#include "StdAfx.h"
#include "WispBase.h"
#include "WispFont.h"
#include "WispMsgBox.h"
#include "DIBData.h"


#define WND_MSG_CONDITION(pWnd)	(m_pModalWnd ==NULL || pWnd->IsChildWndOf(m_pModalWnd) || pWnd==m_pModalWnd)

CWispBase*gpCurWisp=NULL;

CWispBase::CWispBase()
{
	m_Metrics[WISP_SM_CAPTION_CY]=WISP_CAPTION_HEIGHT;
	m_Metrics[WISP_SM_CAPTION_BT_SIZE]=WISP_CAPTION_BT_SIZE;
	m_Metrics[WISP_SM_BORDER_SIZE]=WISP_BORDER_SIZE;
	m_Metrics[WISP_SM_THIN_BORDER_SIZE]=WISP_THIN_BORDER_SIZE;
	m_Metrics[WISP_SM_SCROLL_BAR_SIZE]=WISP_SCROLL_BORDER_SIZE;
	m_Metrics[WISP_SM_FONT_FRAME_HEIGHT]=WISP_FONT_FRAME_HEIGHT;
	m_Metrics[WISP_SM_RESIZE_SPACE]=WISP_RESIZE_SPACE;
	m_pRootWnd=NULL;
	ZeroMemory(m_PalColors,sizeof(m_PalColors));
	STZeroMemory(m_FrameBuffer);
	memcpy(m_PalColors,m_DefColorPal,sizeof(m_PalColors));
	m_bHideMouse = false;
	m_pszDiskList = NULL;
	m_bActive = false;
	GetModulePath(m_CurDir);
	m_DefaultFontType = WISP_FONT_6X12;
	m_iKeyboardLayer=0;
}

CWispBase::~CWispBase()
{
}

bool CWispBase::Init()
{
	int Length;
	PCSTR szBegin,szEnd;
	char szWispDatFN[MAX_FN_LEN],*szFileName;
	WISP_POINT pt;
	gpCurWisp=this;
	m_bActive = false;
	m_pCurDrawObj=NULL;
	m_KeySimulateMouse = false;
///////////////////////////////////////////////////////////////////////////////////////////////////
//Open wisp data disk file
///////////////////////////////////////////////////////////////////////////////////////////////////
	if(m_pszDiskList==NULL)
		m_pszDiskList = "Wisp.dat";
	m_PFSFileIO.ChangeFileIO(gpFileIO);
	Length=TStrCpy(szWispDatFN,m_CurDir);
	if(Length && szWispDatFN[Length-1]!=PATH_SEPARATOR_CHAR)
		TStrCat(szWispDatFN,PATH_SEPARATOR_STR);
	szFileName=&szWispDatFN[TStrLen(szWispDatFN)];
	szBegin = m_pszDiskList;
	while(*szBegin)
	{
		szEnd = TStrChr(szBegin,';');
		if(szEnd)
		{
			TStrCpyLimit(szFileName,szBegin,(int)(szEnd-szBegin)+1);
			szEnd++;
		}
		else
		{
			TStrCpy(szFileName,szBegin);
			szEnd = &szBegin[TStrLen(szBegin)];
		}
		if(m_PFSFileIO.OpenDisk(szWispDatFN,
			#ifdef CODE_OS_NT_DRV
			PFS_FULL_DISK_CACHE|PFS_WRITE_COPY
			#else
			PFS_WRITE_COPY
			#endif
			)==false)
		{
			ReportMsg(WSTR("Error : Fail to open %s!\n"),szWispDatFN);
			m_PFSFileIO.CloseAllDisk();
			return false;
		}
		szBegin = szEnd;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////
	ZeroMemory(m_KeyMap,sizeof(m_KeyMap));
	ZeroMemory(m_LockMap,sizeof(m_LockMap));
	ZeroMemory(&m_MousePT,sizeof(m_MousePT));
	ZeroMemory(&m_PrevMousePT,sizeof(m_PrevMousePT));
	m_bUpdate=false;
	m_LockRef=0;
	m_DefDIB[WISP_DI_CARET].Create(2,12,WISP_DIB_TK_XOR);
	memcpy(m_DefDIB[WISP_DI_CARET].m_FrameBuffer.Buffer,BTCaret,m_DefDIB[WISP_DI_CARET].m_FrameBuffer.BufferSize);
	pt.x=pt.y=8;
	m_pRootWnd=NULL;
	m_bNeedUpdate=false;
	for(int n=0;n<WISP_FONT_COUNT;n++)
	{
		m_FontList[n].LoadChar(&m_PhysFontInfo[n]);
		m_FontList[n].LoadWideChar(&m_PhysFontInfo[n]);
	}
	m_pTopMostRootWnd = NULL;
	m_pHelpTipWnd = NULL;
	m_pModalWnd = NULL;
	m_pDragWnd = NULL;
	m_pMoveWnd = NULL;
	m_RepKeyIndex = WISP_VK_NULL;
	m_CursorTypeBak = m_CursorType = WISP_CT_ARROW;
	m_BaseWndCount = m_WndCount = 0;
	m_KeyLockRef = m_TimerRef = 0;
	m_ModKeyState = 0;
	m_ModelLevel = 0;
	SelectDrawObject(&m_DIBDrawObj);
	return true;
}

void CWispBase::Release()
{
	if(m_pRootWnd)
	{
		m_pRootWnd->Destroy();
		m_pRootWnd=NULL;
	}
	if(m_pCurDrawObj)
		m_pCurDrawObj->Release();
	for(int n=0;n<WISP_DI_COUNT;n++)
		m_DefDIB[n].Destroy();
	for(int n=0;n<WISP_FONT_COUNT;n++)
		m_FontList[n].Destroy();
	m_TimerMap.Clear();
	m_HotKeyList.Clear();
	m_DIBLib.ReleaseAll();
	m_PFSFileIO.CloseAllDisk();
}

bool CWispBase::WakeUpMsgThread()
{
	return true;
}

bool CWispBase::SleepMsgThread()
{
	return true;
}

void CWispBase::EnterCriticalSection()
{
}

void CWispBase::LeaveCriticalSection()
{
}

bool CWispBase::ResizeHostFrame(int Width,int Height)
{
	return false;
}

bool CWispBase::ResizingFrame(int Width,int Height)
{
	return false;
}

bool CWispBase::MoveFrame(int dx,int dy)
{
	return false;
}

void CWispBase::SetMouseCaptureNotify()
{
	
}

void CWispBase::ReleaseMouseCaptureNotify()
{
	
}


void CWispBase::BeginDraw(WISP_RECT*pUpdateRect)
{

}

void CWispBase::EndDraw(WISP_RECT*pUpdateRect)
{

}

void CWispBase::ChangeCursor(IN UINT CursorType,OUT WISP_POINT*pMouseHotPT,OUT WISP_SIZE*pMouseSize,IN CWispDIB*pDIB)
{
	switch(CursorType)
	{
	case WISP_CT_ARROW:
		m_pCurDrawObj->DrawCursorArrow(NULL,NULL);
		break;
	case WISP_CT_DRAG_ARROW:
		m_pCurDrawObj->DrawCursorDrag(NULL,NULL);
		break;
	case WISP_CT_RESIZE_VERT:
		m_pCurDrawObj->DrawCursorResizeVert(NULL,NULL);
		break;
	case WISP_CT_RESIZE_HORZ:
		m_pCurDrawObj->DrawCursorResizeHorz(NULL,NULL);
		break;
	case WISP_CT_RESIZE_LEFT_LEAN:
		m_pCurDrawObj->DrawCursorResizeLeftLean(NULL,NULL);
		break;
	case WISP_CT_RESIZE_RIGHT_LEAN:
		m_pCurDrawObj->DrawCursorResizeRightLean(NULL,NULL);
		break;
	default:
		if(pDIB)
		{
			if(pMouseHotPT)
				*pMouseHotPT = pDIB->m_HotPT;
			if(pMouseSize)
			{
				pMouseSize->cx = pDIB->Width();
				pMouseSize->cy = pDIB->Height();
			}
		}
		break;
	}
}

void CWispBase::ChangeHostCursor(IN NUM_PTR CursorData,OUT WISP_POINT*pMouseHotPT,OUT WISP_SIZE*pMouseSize)
{
}

bool CWispBase::InsertTimerNotify(WISP_TIMER*pTimer)
{
	return true;
}

bool CWispBase::RemoveTimerNotify(WISP_TIMER*pTimer)
{
	return true;
}

void CWispBase::AdjustColor()
{
	for(int n=0;n<MAX_SYSTEM_COLOR;n++)
	{
		m_pCurDrawObj->m_crSystem[n]=FindFitColor(m_pCurDrawObj->m_crSystem[n],m_PalColors);
	}
}

void CWispBase::OnFrameBufferBppChg(int Bpp)
{
	m_FrameBuffer.Bpp = Bpp;
	switch(m_FrameBuffer.Bpp)
	{
	case 4:
		m_FrameBuffer.pDrawHAL = &m_DrawHAL4Bit;
	case 8:
		m_FrameBuffer.pDrawHAL = &m_DrawHAL8Bit;
		break;
	case 16:
		m_FrameBuffer.pDrawHAL = &m_DrawHAL16Bit;
		break;
	case 24:
		m_FrameBuffer.pDrawHAL = &m_DrawHAL24Bit;
		break;
	case 32:
		m_FrameBuffer.pDrawHAL = &m_DrawHAL32Bit;
		break;
	default:
		m_FrameBuffer.pDrawHAL = &m_NotSupportDrawHAL;
		break;
	}
	if(m_FrameBuffer.Bpp==8)
	{
		LoadPalette();
		AdjustColor();
	}
}

void CWispBase::SetMousePos(int x,int y)
{
	m_PrevMousePT.x = m_MousePT.x = x;
	m_PrevMousePT.y = m_MousePT.y = y;
}

void CWispBase::LockUpdate()
{
	m_LockRef++;
}

void CWispBase::UnlockUpdate()
{
	if(m_LockRef>0)
		m_LockRef--;
}

void CWispBase::LockKey()
{
	m_KeyLockRef++;
}

void CWispBase::UnlockKey()
{
	if(m_KeyLockRef>0)
		m_KeyLockRef--;
}

void CWispBase::LockTimer()
{
	m_TimerRef++;
}

void CWispBase::UnlockTimer()
{
	if(m_TimerRef>0)
		m_TimerRef--;	
}

COLORREF CWispBase::GetPalColor(int Index)
{
	return m_PalColors[Index];
}

bool CWispBase::SetPalColor(int Index,COLORREF Color)
{
	m_PalColors[Index]=Color;
	return true;
}

void CWispBase::LoadPalette()
{
	for(int n=0;n<256;n++)
		SetPalColor(n,m_PalColors[n]);
}

CWispDIB*CWispBase::GetDefDIB(IN UINT ID)
{
	if(ID>=WISP_DI_COUNT)
		return NULL;
	return &m_DefDIB[ID];
}

void CWispBase::ChangeCursorType(IN UINT DIBID)
{
	if(m_CursorType==DIBID)
		return;
	m_CursorTypeBak = m_CursorType;
	m_CursorType = DIBID;
	m_pCursorDIBBak = m_pCursorDIB;
	m_pCursorDIB = NULL;
	ChangeCursor(m_CursorType,&m_MouseHotPT,&m_MouseSize,NULL);
	if(m_bHideMouse==false)
		RedrawNextTime();
}

void CWispBase::ChangeCursorType(IN CWispDIB*pDIB)
{
	if(m_pCursorDIB==pDIB)
		return;
	m_CursorTypeBak = m_CursorType;
	m_CursorType = WISP_CT_USER_DIB_TYPE;
	m_pCursorDIBBak = m_pCursorDIB;
	m_pCursorDIB = pDIB;
	ChangeCursor(m_CursorType,&m_MouseHotPT,&m_MouseSize,m_pCursorDIB);
	if(m_bHideMouse==false)
		RedrawNextTime();
}

void CWispBase::ChangeHostCursorType(IN NUM_PTR CursorData)
{
	m_CursorTypeBak = m_CursorType;
	m_CursorType = WISP_CT_USER_DATA_TYPE;
	ChangeHostCursor(CursorData,&m_MouseHotPT,&m_MouseSize);
	if(m_bHideMouse==false)
		RedrawNextTime();
}

void CWispBase::RestorCursorType()
{
	if(m_CursorType == WISP_CT_USER_DIB_TYPE)
	{
		m_pCursorDIB = m_pCursorDIBBak;
	}
	else if(m_CursorType == WISP_CT_USER_DATA_TYPE)
	{
		m_pCursorDIB = NULL;
	}
	m_CursorType = m_CursorTypeBak;
	m_pCursorDIB = m_pCursorDIBBak;
	ChangeCursor(m_CursorType,&m_MouseHotPT,&m_MouseSize,m_pCursorDIB);
	if(m_bHideMouse==false)
		RedrawNextTime();
}

void CWispBase::BeginMoveWnd(CWispBaseWnd*pWnd)
{
	WISP_MSG Msg;
	if(pWnd==NULL)
		pWnd = m_pRootWnd;
	Msg.hWnd = pWnd;
	Msg.Msg = WISP_WM_BEGIN_MOVE;
	m_pMoveWnd = pWnd;
	m_pMoveWnd->m_State|=WISP_WST_MOVING;
	SendMessage(&Msg);
}

void CWispBase::EndMoveWnd()
{
	WISP_MSG Msg;
	if(m_pMoveWnd==NULL || m_pMoveWnd->IsWindow()==false)
		return;
	Msg.hWnd = m_pMoveWnd;
	Msg.Msg = WISP_WM_END_MOVE;
	m_pMoveWnd->m_State&=~WISP_WST_MOVING;
	SendMessage(&Msg);
	m_pMoveWnd = NULL;
}

void CWispBase::OnMousePosChg(IN int PosX,IN int PosY)
{
	WISP_INPUT_MSG*pMsg = m_InputMsgQueue.Append();
	pMsg->InputMsg = WISP_INPUT_MOUSE_POS_CHG;
	pMsg->MousePosChg.PosX = PosX;
	pMsg->MousePosChg.PosY = PosY;
}

void CWispBase::DispatchMousePosChg(IN int PosX,IN int PosY)
{
	UINT HitAreaType,HitCtrlType,HitReizeAreaType;
	WISP_MSG Msg;
	CWispWnd*pScrollWnd;
	CWispBaseWnd*pWispWnd;
	int DeltaX,DeltaY;
	if(m_MousePT.x==PosX && m_MousePT.y==PosY)
		return;
	m_MousePT.x=PosX;
	m_MousePT.y=PosY;
	//CODE_DEBUG_OUTPUT("x = %d,y = %d\n",m_MousePT.x,m_MousePT.y);
	if(m_MousePT.x<0)
		m_MousePT.x=0;
	if(m_MousePT.y<0)
		m_MousePT.y=0;
	if(m_MousePT.x>=m_FrameBuffer.Width)
		m_MousePT.x=m_FrameBuffer.Width-1;
	if(m_MousePT.y>=m_FrameBuffer.Height)
		m_MousePT.y=m_FrameBuffer.Height-1;
	DeltaX = m_MousePT.x-m_PrevMousePT.x;
	DeltaY = m_MousePT.y-m_PrevMousePT.y;
	m_PrevMousePT=m_MousePT;
	if(m_bHideMouse==false)
		RedrawNextTime();
	if(m_pMoveWnd && (m_pMoveWnd->m_State&WISP_WST_MOVING))
	{
		m_pMoveWnd->Move(DeltaX,DeltaY);
		goto ExitOnMousePosChg;
	}
	pWispWnd=WindowFromPoint(&m_MousePT,m_pRootWnd);
	CODE_ASSERT(pWispWnd);
	if(pWispWnd==NULL)
		goto ExitOnMousePosChg;
	if(pWispWnd==NULL || pWispWnd->IsDisabled())
		goto ExitOnMousePosChg;
	if(gpCurWisp->m_pDragWnd==m_pMouseEventWnd)
	{
		WISP_MSG Msg;
		Msg.hWnd = m_pMouseEventWnd;
		Msg.Msg = WISP_WM_DRAG_MOVE;
		Msg.DragEvent.BeginMouseWndPT = m_BeginPT;
		Msg.DragEvent.DeltaX = DeltaX;
		Msg.DragEvent.DeltaY = DeltaY;
		gpCurWisp->SendMessage(&Msg);
		goto ExitOnMousePosChg;
	}
	if(pWispWnd->m_State&WISP_WST_SIZING)
	{
		pWispWnd->Move(	-DeltaX*((CWispWnd*)pWispWnd)->m_SignResizeX,-DeltaY*((CWispWnd*)pWispWnd)->m_SignResizeY);
		if(((CWispWnd*)pWispWnd)->Resize(
			pWispWnd->m_WindowRect.cx-DeltaX*((CWispWnd*)pWispWnd)->m_SignResizeDX,
			pWispWnd->m_WindowRect.cy-DeltaY*((CWispWnd*)pWispWnd)->m_SignResizeDY)==false)
		{
			m_pMouseEventWnd->m_State&=~WISP_WST_SIZING;
			ChangeCursorType(WISP_CT_ARROW);
		}
		goto ExitOnMousePosChg;
	}
	if(pWispWnd!=m_pMouseEventWnd)
	{
		if(m_pMouseEventWnd->m_State&WISP_WST_MOVING)
		{
			m_pMouseEventWnd->Move(DeltaX,DeltaY);
			goto ExitOnMousePosChg;
		}
		if(m_pMouseEventWnd->m_State&WISP_WST_SIZING)
		{
			m_pMouseEventWnd->Move( -DeltaX*((CWispWnd*)m_pMouseEventWnd)->m_SignResizeX,-DeltaY*((CWispWnd*)m_pMouseEventWnd)->m_SignResizeY);
			if(((CWispWnd*)m_pMouseEventWnd)->Resize(
				m_pMouseEventWnd->m_WindowRect.cx-DeltaX*((CWispWnd*)m_pMouseEventWnd)->m_SignResizeDX,
				m_pMouseEventWnd->m_WindowRect.cy-DeltaY*((CWispWnd*)m_pMouseEventWnd)->m_SignResizeDY)==false)
			{
				m_pMouseEventWnd->m_State&=~WISP_WST_SIZING;
				ChangeCursorType(WISP_CT_ARROW);
			}
			goto ExitOnMousePosChg;
		}
		Msg.hWnd = pWispWnd;
		Msg.Msg = WISP_WM_HIT_TEST;
		Msg.HitTest.bKeyDown=m_KeyMap[WISP_VK_LBUTTON];
		Msg.HitTest.HitAreaType = WISP_HIT_WND_NON;
		Msg.HitTest.HitCtrlType = WISP_HIT_CTRL_NON;
		SendMessage(&Msg);
		HitAreaType = Msg.HitTest.HitAreaType;
		HitCtrlType = Msg.HitTest.HitCtrlType;
		if((m_pMouseEventWnd->m_Style&WISP_WS_ADV_WND) && ((CWispWnd*)m_pMouseEventWnd)->m_bInResizeArea)
			ChangeCursorType(WISP_CT_ARROW);
		Msg.hWnd=m_pMouseEventWnd;
		Msg.Msg=WISP_WM_MOUSE_LEAVE;
		if(m_pMouseEventWnd->m_Style & WISP_WS_ADV_WND)
		{
			pScrollWnd = (CWispWnd*)m_pMouseEventWnd;
			if(pScrollWnd->m_ScrollBar[WISP_SB_VERT] && pScrollWnd->m_ScrollBar[WISP_SB_VERT]->State == STATUS_DOWN)
			{
				Msg.Msg	= WISP_WM_VERT_SCROLL_MOVE;
			}
			else if(pScrollWnd->m_ScrollBar[WISP_SB_HORZ] && pScrollWnd->m_ScrollBar[WISP_SB_HORZ]->State == STATUS_DOWN)
			{
				Msg.Msg	= WISP_WM_HORZ_SCROLL_MOVE;
			}
		}
		Msg.MouseEvent.HitAreaType=HitAreaType;
		Msg.MouseEvent.HitCtrlType=HitCtrlType;
		Msg.MouseEvent.hWndMouseAt=pWispWnd;
		Msg.MouseEvent.DeltaX=DeltaX;
		Msg.MouseEvent.DeltaY=DeltaY;
		Msg.MouseEvent.DeltaZ=0;
		SendMessage(&Msg);
		if(m_pMouseEventWnd==pWispWnd)
		{
			Msg.hWnd=m_pMouseEventWnd;
			Msg.Msg=WISP_WM_MOUSE_ENTER;
			SendMessage(&Msg);
		}
		goto ExitOnMousePosChg;
	}
	if(WND_MSG_CONDITION(pWispWnd))
	{
		Msg.hWnd = pWispWnd;
		Msg.Msg = WISP_WM_HIT_TEST;
		Msg.HitTest.bKeyDown = false;
		Msg.HitTest.HitAreaType = WISP_HIT_WND_NON;
		Msg.HitTest.HitCtrlType = WISP_HIT_CTRL_NON;
		SendMessage(&Msg);
		HitAreaType = Msg.HitTest.HitAreaType;
		HitCtrlType = Msg.HitTest.HitCtrlType;
		HitReizeAreaType = Msg.HitTest.HitAreaType & WISP_HIT_WND_RESIZE_MASK;
		if(HitReizeAreaType)
		{
			switch(HitReizeAreaType)
			{
			case WISP_HIT_WND_RESIZE_LEFT:
			case WISP_HIT_WND_RESIZE_RIGHT:
				HitReizeAreaType = WISP_CT_RESIZE_HORZ;
				break;
			case WISP_HIT_WND_RESIZE_TOP:
			case WISP_HIT_WND_RESIZE_BOTTOM:
				HitReizeAreaType = WISP_CT_RESIZE_VERT;
				break;
			case WISP_HIT_WND_RESIZE_LEFT|WISP_HIT_WND_RESIZE_TOP:
			case WISP_HIT_WND_RESIZE_RIGHT|WISP_HIT_WND_RESIZE_BOTTOM:
				HitReizeAreaType = WISP_CT_RESIZE_LEFT_LEAN;
				break;
			case WISP_HIT_WND_RESIZE_LEFT|WISP_HIT_WND_RESIZE_BOTTOM:
			case WISP_HIT_WND_RESIZE_RIGHT|WISP_HIT_WND_RESIZE_TOP:
				HitReizeAreaType = WISP_CT_RESIZE_RIGHT_LEAN;
				break;
			}
			if(m_pMouseEventWnd->m_Style&WISP_WS_ADV_WND)
			{
				((CWispWnd*)m_pMouseEventWnd)->m_bInResizeArea=true;
				ChangeCursorType(HitReizeAreaType);
			}
		}
		else
		{
			if( (m_pMouseEventWnd->m_Style&WISP_WS_ADV_WND) && ((CWispWnd*)m_pMouseEventWnd)->m_bInResizeArea)
			{
				ChangeCursorType(WISP_CT_ARROW);
				((CWispWnd*)m_pMouseEventWnd)->m_bInResizeArea=false;
			}
		}
		Msg.hWnd=pWispWnd;
		Msg.Msg=WISP_WM_MOUSE_MOVE;
		Msg.MouseEvent.HitAreaType = HitAreaType;
		Msg.MouseEvent.HitCtrlType = HitCtrlType;
		Msg.MouseEvent.hWndMouseAt=pWispWnd;
		Msg.MouseEvent.DeltaX=DeltaX;
		Msg.MouseEvent.DeltaY=DeltaY;
		Msg.MouseEvent.DeltaZ=0;
		if(m_MouseMoveHookWndList.Count())
		{
			for(CWndList::IT Iter = m_MouseMoveHookWndList.Begin();Iter!=m_MouseMoveHookWndList.End();Iter++)
			{
				if(*Iter!=Msg.hWnd)
				{
					Msg.hWnd = *Iter;
					if(SendMessage(&Msg)==false)
						goto ExitOnMousePosChg;
				}
			}
		}
		Msg.hWnd=pWispWnd;
		if(pWispWnd->m_Style & WISP_WS_ADV_WND)
		{
			pScrollWnd = (CWispWnd*)pWispWnd;
			if(pScrollWnd->m_ScrollBar[WISP_SB_VERT] && pScrollWnd->m_ScrollBar[WISP_SB_VERT]->State == STATUS_DOWN)
				Msg.Msg	= WISP_WM_VERT_SCROLL_MOVE;
			else if(pScrollWnd->m_ScrollBar[WISP_SB_HORZ] && pScrollWnd->m_ScrollBar[WISP_SB_HORZ]->State == STATUS_DOWN)
				Msg.Msg	= WISP_WM_HORZ_SCROLL_MOVE;		
		}
		SendMessage(&Msg);
	}
ExitOnMousePosChg:
	return;
}

void CWispBase::OnMouseMove(IN int DeltaX,IN int DeltaY)
{
	WISP_INPUT_MSG*pMsg=m_InputMsgQueue.Append();
	pMsg->InputMsg = WISP_INPUT_MOUSE_MOVE;
	pMsg->MouseMove.DeltaX = DeltaX;
	pMsg->MouseMove.DeltaY = DeltaY;
}

void CWispBase::DispatchMouseMove(IN int DeltaX,IN int DeltaY)
{
	int NewPosX,NewPosY;
	NewPosX=m_MousePT.x+DeltaX;
	NewPosY=m_MousePT.y+DeltaY;
	OnMousePosChg(NewPosX,NewPosY);
}

void CWispBase::OnMouseWheel(IN int DeltaZ)
{
	WISP_INPUT_MSG*pMsg=m_InputMsgQueue.Append();
	pMsg->InputMsg = WISP_INPUT_MOUSE_WHEEL;
	pMsg->MouseWheel.DeltaZ = DeltaZ;
}

void CWispBase::DispatchMouseWheel(IN int DeltaZ)
{
	if(m_pFocusWnd==NULL)
		return;
	WISP_MSG Msg;
	Msg.hWnd = m_pFocusWnd;
	Msg.Msg = WISP_WM_MOUSE_WHEEL;
	Msg.MouseEvent.DeltaX = 0;
	Msg.MouseEvent.DeltaY = 0;
	Msg.MouseEvent.DeltaZ = DeltaZ;
	Msg.MouseEvent.HitAreaType = WISP_HIT_WND_NON;
	Msg.MouseEvent.HitCtrlType = WISP_HIT_CTRL_NON;
	Msg.MouseEvent.hWndMouseAt = m_pFocusWnd;
	SendMessage(&Msg);
}

void CWispBase::OnMouseButtonDBClick(UINT KeyType)
{
	WISP_INPUT_MSG*pMsg=m_InputMsgQueue.Append();
	pMsg->InputMsg = WISP_INPUT_MOUSE_BT_DB_CLICK;
	pMsg->MouseBTDBClick.KeyType = KeyType;
}

void CWispBase::DispatchMouseButtonDBClick(UINT KeyType)
{
	WISP_MSG Msg;
	if(m_pFocusWnd==NULL)
		return;
	switch(m_LastMouseClickHitAreaType)
	{
	case WISP_HIT_WND_CLIENT:
	case WISP_HIT_WND_NON_CLIENT:
		Msg.hWnd = m_pFocusWnd;
		Msg.Msg = WISP_WM_MOUSE_DBCLICK;
		Msg.KeyEvent.bKeyDown = true;
		Msg.KeyEvent.ScanCode = 0;
		Msg.KeyEvent.KeyType = KeyType;
		Msg.KeyEvent.HitAreaType = m_LastMouseClickHitAreaType;
		Msg.KeyEvent.HitCtrlType = m_LastMouseClickHitCtrlType;
		SendMessage(&Msg);
		break;
	}
}

void CWispBase::OnKeyEvent(IN UINT KeyType,IN bool bKeyDown,IN UINT ScanCode)
{
	WISP_INPUT_MSG*pMsg=m_InputMsgQueue.Append();
	pMsg->InputMsg = WISP_INPUT_KEY_EVENT;
	pMsg->KeyEvent.KeyType  = KeyType;
	pMsg->KeyEvent.bKeyDown = bKeyDown;
	pMsg->KeyEvent.ScanCode = ScanCode;
}

void CWispBase::DispatchKeyEvent(IN UINT KeyType,IN bool bKeyDown,IN UINT ScanCode)
{
	if(m_KeyLockRef)
		return;
	if(KeyType>WISP_VK_KEYBOARD_START)
		OnProcessKeyEvent(KeyType,bKeyDown,ScanCode);
	else
		OnProcessMouseKeyEvent(KeyType,bKeyDown,ScanCode);
}

void CWispBase::OnTimer(int MilliSec)
{
	WISP_INPUT_MSG*pMsg=m_InputMsgQueue.Append();
	pMsg->InputMsg = WISP_INPUT_TIMER;
	pMsg->Timer.MilliSec  = MilliSec;
}

void CWispBase::DispatchTimer(int MilliSec)
{
	WISP_CHAR Char;
	WISP_MSG Msg;
	WISP_TIMER*pTimer;
	WISP_TIMER_KEY*pTimerKey;
	CWispBaseWnd*pMsgWnd;
	if(m_TimerRef>0)
		return;
	if(m_RepKeyIndex!=WISP_VK_NULL)
	{
		m_RepKeyElapse+=MilliSec;
		if(m_KeySimulateMouse)
			KeySimulateMouse(m_RepKeyIndex,true);
		if(m_RepKeyElapse>=m_RepKeyPeriod)
		{
			m_RepKeyElapse-=m_RepKeyPeriod;
			if(m_RepKeyIndex<WISP_VK_KEYBOARD_START)
			{
				if(m_RepKeyPeriod == WISP_MOUSE_KEY_REPEAT_DELAY)
					m_RepKeyPeriod = WISP_MOUSE_KEY_REPEAT_PERIOD;
			}
			else
			{
				if(m_RepKeyPeriod == WISP_KEY_REPEAT_DELAY)
					m_RepKeyPeriod = WISP_KEY_REPEAT_PERIOD;
			}
			Msg.hWnd = m_pFocusWnd;
			Msg.Msg = WISP_WM_KEY_EVENT;
			if(m_RepKeyIndex == WISP_VK_LBUTTON)
			{
				WISP_MSG HitTestMsg;
				HitTestMsg.hWnd = m_pFocusWnd;
				HitTestMsg.Msg = WISP_WM_HIT_TEST;
				HitTestMsg.HitTest.bKeyDown = true;
				HitTestMsg.HitTest.HitAreaType = WISP_HIT_WND_NON;
				HitTestMsg.HitTest.HitCtrlType = WISP_HIT_CTRL_NON;
				SendMessage(&HitTestMsg);
				Msg.KeyEvent.HitAreaType = HitTestMsg.KeyEvent.HitAreaType;
				Msg.KeyEvent.HitCtrlType = HitTestMsg.KeyEvent.HitCtrlType;
			}
			Msg.KeyEvent.KeyType = m_RepKeyIndex;
			Msg.KeyEvent.bKeyDown = true;
			SendMessage(&Msg);
			Char=IsCharKey(m_RepKeyIndex);
			if(Char)
			{
				pMsgWnd = m_pFocusWnd;
				if(WND_MSG_CONDITION(pMsgWnd)==false)
					pMsgWnd=m_pModalWnd;
				Msg.hWnd = pMsgWnd;
				Msg.Msg = WISP_WM_CHAR;
				Msg.Char.Char=Char;
				Msg.Char.nRepeat=1;
				SendMessage(&Msg);
			}
		}
	}
	for(CTimerMap::IT Iter=m_TimerMap.Begin();Iter!=m_TimerMap.End();)
	{
		pTimer=&(*Iter);
		pTimerKey = &Iter.Key();
		Iter++;
		if(MilliSec <= pTimer->Period)
		{
			pTimer->Elapse+=MilliSec;
			if(pTimer->Elapse>pTimer->Period)
			{
				pTimer->Elapse-=pTimer->Period;
				Msg.hWnd = pTimerKey->hWnd;
				Msg.Msg = WISP_WM_TIMER;
				Msg.Timer.ID = pTimerKey->ID;
				Msg.Timer.UserData = pTimer->UserData;
				Msg.Timer.UserPtr = pTimer->UserPtr;
				SendMessage(&Msg);
			}
		}
	}
}

WISP_CHAR CWispBase::IsCharKey(IN UINT KeyType)
{
	bool bLowCase=true;
	if(m_KeyMap[WISP_VK_SHIFT])
		bLowCase=!bLowCase;
	if(m_LockMap[WISP_VK_CAPS_LOCK])
		bLowCase=!bLowCase;
	return  (WISP_CHAR)m_VKKeyChar[m_iKeyboardLayer][KeyType*2+bLowCase];
}

bool CWispBase::KeySimulateMouse(IN UINT KeyType,IN bool bKeyDown)
{
	int x,y;
	x=y=0;
	switch(KeyType)
	{
	case WISP_VK_PAGE_UP:
	case WISP_VK_END:
		DispatchKeyEvent(WISP_VK_LBUTTON,bKeyDown,0);
		return true;
	case WISP_VK_PAGE_DOWN:
		DispatchKeyEvent(WISP_VK_RBUTTON,bKeyDown,0);
		return true;
	case WISP_VK_UP:
	case WISP_VK_DOWN:
	case WISP_VK_LEFT:
	case WISP_VK_RIGHT:
		if(m_KeyMap[WISP_VK_UP])
			y=-m_KeySimDelta;
		if(m_KeyMap[WISP_VK_DOWN])
			y = m_KeySimDelta;
		if(m_KeyMap[WISP_VK_LEFT])
			x = -m_KeySimDelta;
		if(m_KeyMap[WISP_VK_RIGHT])
			x += m_KeySimDelta;
		if(m_KeySimDelta<20)
			m_KeySimDelta++;
		break;
	default:
		return false;
	}
	DispatchMousePosChg(m_PrevMousePT.x+x,m_PrevMousePT.y+y);
	return true;
}

bool CWispBase::OnProcessKeyEvent(IN UINT KeyType,IN bool bKeyDown,IN UINT ScanCode)
{
	WISP_CHAR Char;
	WISP_MSG Msg;
	CWispBaseWnd*pMsgWnd;
#ifdef WISP_TIMER_SIM_KEY_REPEAT
	if(m_KeyMap[KeyType]==bKeyDown)
		return false;
#endif
	pMsgWnd = m_pFocusWnd;
	if(pMsgWnd==NULL)
		return false;
	if(WND_MSG_CONDITION(pMsgWnd)==false)
		pMsgWnd=m_pModalWnd;
	m_KeyMap[KeyType]=bKeyDown;
	if(KeyType == WISP_VK_LSHIFT || KeyType == WISP_VK_RSHIFT)
	{
		m_KeyMap[WISP_VK_SHIFT] = m_KeyMap[WISP_VK_LSHIFT] | m_KeyMap[WISP_VK_RSHIFT];
	}
	if(KeyType == WISP_VK_LALT || KeyType == WISP_VK_RALT)
	{
		m_KeyMap[WISP_VK_ALT] = m_KeyMap[WISP_VK_LALT] | m_KeyMap[WISP_VK_RALT];
	}
	if(KeyType == WISP_VK_LCONTROL || KeyType == WISP_VK_RCONTROL)
	{
		m_KeyMap[WISP_VK_CONTROL] = m_KeyMap[WISP_VK_LCONTROL] | m_KeyMap[WISP_VK_RCONTROL];
	}
	if(m_KeyMap[WISP_VK_SHIFT])
		m_ModKeyState |= WISP_MOD_SHIFT;
	else
		m_ModKeyState &= ~WISP_MOD_SHIFT;
	if(m_KeyMap[WISP_VK_ALT])
		m_ModKeyState |= WISP_MOD_ALT;
	else
		m_ModKeyState &= ~WISP_MOD_ALT;
	if(m_KeyMap[WISP_VK_CONTROL])
		m_ModKeyState |= WISP_MOD_CTRL;
	else
		m_ModKeyState &= ~WISP_MOD_CTRL;

	if(m_KeySimulateMouse)
	{
		if(bKeyDown)
		{
			if(KeyType!=WISP_VK_END && KeyType!=WISP_VK_PAGE_DOWN && KeyType!=WISP_VK_PAGE_UP)
			{
				m_RepKeyIndex = KeyType;
				m_RepKeyElapse = 0;
				m_RepKeyPeriod = WISP_KEY_REPEAT_DELAY;
				m_KeySimDelta = 1;
			}
		}
		else
		{
			if(m_RepKeyIndex==KeyType)
				m_RepKeyIndex = WISP_VK_NULL;
		}
		if(KeySimulateMouse(KeyType,bKeyDown))
			return true;
	}
	if(bKeyDown && m_HotKeyList.Count())
	{
		for(CHotKeyList::IT Iter = m_HotKeyList.Begin();Iter!=m_HotKeyList.End();Iter++)
		{
			if(Iter->KeyType == KeyType && (Iter->Modifier==0 || Iter->Modifier == m_ModKeyState) )
			{
				WISP_MSG Msg;
				Msg.hWnd = Iter->hWnd;
				Msg.Msg = WISP_WM_EVENT;
				Msg.Command.CmdID = Iter->EventID;
				Msg.Command.CmdMsg = WISP_CMD_HOTKEY;
				if(Iter->Style & WISP_HKS_CHILD_WND)
				{
					if(pMsgWnd->IsChildWndOf(Msg.hWnd)==false && pMsgWnd!=Msg.hWnd)
						continue;
				}
				SendMessage(&Msg);
			}
		}
	}
	Msg.hWnd = pMsgWnd;
	Msg.Msg = WISP_WM_KEY_EVENT;
	Msg.KeyEvent.KeyType = KeyType|m_ModKeyState;
	Msg.KeyEvent.bKeyDown = bKeyDown;
	Msg.KeyEvent.ScanCode = ScanCode;
	if(m_KeyHookWndList.Count())
	{
		for(CWndList::IT Iter = m_KeyHookWndList.Begin();Iter!=m_KeyHookWndList.End();Iter++)
		{
			if(*Iter!=Msg.hWnd)
			{
				Msg.hWnd = *Iter;
				SendMessage(&Msg);
			}
		}
	}
	if(pMsgWnd->IsDisabled()==false)
	{
		Msg.hWnd = pMsgWnd;
		if(SendMessage(&Msg)==false)
			return true;
	}
	if(bKeyDown)
	{
		if(m_KeyMap[WISP_VK_CONTROL] && m_KeyMap[WISP_VK_ALT])
		{
			if(m_KeyMap[WISP_VK_F1])
			{
				SelectDrawObject(&m_DefDrawObj);
				m_pRootWnd->Update();
			}
			else if(m_KeyMap[WISP_VK_F2])
			{
				SelectDrawObject(&m_DIBDrawObj);
				m_pRootWnd->Update();
			}
		}
#ifdef WISP_TIMER_SIM_KEY_REPEAT
		m_RepKeyIndex = KeyType;
		m_RepKeyElapse = 0;
		m_RepKeyPeriod = WISP_KEY_REPEAT_DELAY;
#endif
		if(m_ModKeyState==0 || m_ModKeyState==WISP_MOD_SHIFT)
		{
			switch(KeyType)
			{
			case WISP_VK_CAPITAL:
				m_LockMap[WISP_VK_CAPS_LOCK]=!m_LockMap[WISP_VK_CAPS_LOCK];
				break;
			}
			Char=IsCharKey(KeyType);
			if(Char)
			{
				pMsgWnd = m_pFocusWnd;
				if(WND_MSG_CONDITION(pMsgWnd)==false)
					pMsgWnd=m_pModalWnd;
				Msg.hWnd = pMsgWnd;
				Msg.Msg = WISP_WM_CHAR;
				Msg.Char.Char=Char;
				Msg.Char.nRepeat=1;
				PostMessage(&Msg);
				for(CWndList::IT Iter = m_KeyHookWndList.Begin();Iter!=m_KeyHookWndList.End();Iter++)
				{
					if(*Iter!=Msg.hWnd)
					{
						Msg.hWnd = *Iter;
						PostMessage(&Msg);
					}
				}
			}
		}
	}
	else
	{
#ifdef WISP_TIMER_SIM_KEY_REPEAT
		if(m_RepKeyIndex == KeyType)
			m_RepKeyIndex = WISP_VK_NULL;
#endif
	}
	return true;
}

bool CWispBase::OnProcessMouseKeyEvent(IN UINT KeyType,IN bool bKeyDown,IN UINT ScanCode)
{
	UINT HitAreaType,HitCtrlType;
	CWispBaseWnd*pMsgWnd;
	WISP_MSG Msg;
	m_KeyMap[KeyType]=bKeyDown;
	if(m_pMoveWnd && (m_pMoveWnd->m_State&WISP_WST_MOVING) && KeyType == WISP_VK_LBUTTON && bKeyDown==false)
	{
		EndMoveWnd();
		return true;
	}
	if(KeyType == WISP_VK_LBUTTON && bKeyDown)
	{
		pMsgWnd=WindowFromPoint(&m_MousePT,m_pRootWnd);
		if(WND_MSG_CONDITION(pMsgWnd)==false)
			pMsgWnd=m_pModalWnd;
		CODE_ASSERT(pMsgWnd);
		if(pMsgWnd==NULL)
			return false;
		if(pMsgWnd->IsDisabled())
			return true;
		if(pMsgWnd!=m_pFocusWnd)
			pMsgWnd->Focus();
		Msg.hWnd = pMsgWnd;
	}
	else
	{
		pMsgWnd = m_pMouseEventWnd;
		if(WND_MSG_CONDITION(pMsgWnd)==false)
			pMsgWnd=m_pModalWnd;
		if(pMsgWnd->IsDisabled())
			return true;
		Msg.hWnd = pMsgWnd;
	}
	if(bKeyDown)
	{
		if(Msg.hWnd->m_AdvStyle & WISP_WAS_DRAG_WND)
		{
			if((pMsgWnd->m_State&(WISP_WST_MOVING|WISP_WST_MAX))==0)
			{
				pMsgWnd->m_State|=WISP_WST_MOVING;
				Msg.Msg = WISP_WM_BEGIN_MOVE;
				SendMessage(&Msg);
			}
		}
		else if(Msg.hWnd->m_Style & WISP_WS_ADV_WND)
		{
			Msg.Msg = WISP_WM_HIT_TEST;
			Msg.HitTest.bKeyDown=bKeyDown;
			Msg.HitTest.HitAreaType = WISP_HIT_WND_NON;
			Msg.HitTest.HitCtrlType = WISP_HIT_CTRL_NON;
			SendMessage(&Msg);
			m_LastMouseClickHitAreaType = Msg.HitTest.HitAreaType;
			m_LastMouseClickHitCtrlType = Msg.HitTest.HitCtrlType;
			switch(Msg.HitTest.HitAreaType)
			{
			case WISP_HIT_WND_CLIENT:
			case WISP_HIT_WND_NON_CLIENT:
				HitAreaType = Msg.HitTest.HitAreaType;
				HitCtrlType = Msg.HitTest.HitCtrlType;
				Msg.KeyEvent.HitAreaType = HitAreaType;
				Msg.KeyEvent.HitCtrlType = HitCtrlType;
				Msg.KeyEvent.KeyType = KeyType;
				Msg.KeyEvent.bKeyDown = bKeyDown;
				Msg.KeyEvent.ScanCode = ScanCode;
				Msg.Msg = WISP_WM_KEY_EVENT;
				SendMessage(&Msg);
				break;
			case WISP_HIT_WND_MOVE:
				if(KeyType == WISP_VK_LBUTTON && (pMsgWnd->m_State&(WISP_WST_MOVING|WISP_WST_MAX))==0)
				{
					BeginMoveWnd(pMsgWnd);
				}
				break;
			default:
				if(KeyType == WISP_VK_LBUTTON && (Msg.HitTest.HitAreaType & WISP_HIT_WND_RESIZE_MASK))
				{
					((CWispWnd*)pMsgWnd)->m_SignResizeX=
					((CWispWnd*)pMsgWnd)->m_SignResizeDX=
					((CWispWnd*)pMsgWnd)->m_SignResizeY=
					((CWispWnd*)pMsgWnd)->m_SignResizeDY=0;
					if(Msg.HitTest.HitAreaType & WISP_HIT_WND_RESIZE_LEFT)
					{
						((CWispWnd*)pMsgWnd)->m_SignResizeX=-1;
						((CWispWnd*)pMsgWnd)->m_SignResizeDX=1;
					}
					if(Msg.HitTest.HitAreaType & WISP_HIT_WND_RESIZE_RIGHT)
					{
						((CWispWnd*)pMsgWnd)->m_SignResizeX=0;
						((CWispWnd*)pMsgWnd)->m_SignResizeDX=-1;
					}
					if(Msg.HitTest.HitAreaType & WISP_HIT_WND_RESIZE_TOP)
					{
						((CWispWnd*)pMsgWnd)->m_SignResizeY=-1;
						((CWispWnd*)pMsgWnd)->m_SignResizeDY=1;
					}
					if(Msg.HitTest.HitAreaType & WISP_HIT_WND_RESIZE_BOTTOM)
					{
						((CWispWnd*)pMsgWnd)->m_SignResizeY=0;
						((CWispWnd*)pMsgWnd)->m_SignResizeDY=-1;
					}
					pMsgWnd->m_State|=WISP_WST_SIZING;
				}
				break;
			}
		}
		else
		{//Wnd is CWispBaseWnd
			Msg.Msg = WISP_WM_HIT_TEST;
			Msg.HitTest.bKeyDown=bKeyDown;
			Msg.HitTest.HitAreaType = WISP_HIT_WND_NON;
			Msg.HitTest.HitCtrlType = WISP_HIT_CTRL_NON;
			SendMessage(&Msg);
			Msg.Msg = WISP_WM_KEY_EVENT;
			HitAreaType = Msg.HitTest.HitAreaType;
			HitCtrlType = Msg.HitTest.HitCtrlType;
			Msg.KeyEvent.HitAreaType = Msg.HitTest.HitAreaType;
			Msg.KeyEvent.HitCtrlType = Msg.HitTest.HitCtrlType;
			Msg.KeyEvent.KeyType = KeyType;
			Msg.KeyEvent.bKeyDown = bKeyDown;
			Msg.KeyEvent.ScanCode = ScanCode;
			/*
			if(m_KeyHookWndList.Count())
			{
				for(CWndList::IT Iter = m_KeyHookWndList.Begin();Iter!=m_KeyHookWndList.End();Iter++)
				{
					if(*Iter!=Msg.hWnd)
					{
						Msg.hWnd = *Iter;
						SendMessage(&Msg);
					}
				}
			}*/
			Msg.hWnd = pMsgWnd;
			SendMessage(&Msg);
		}
	}
	else
	{//bKeyDown is false
		if(m_RepKeyIndex == KeyType)
			m_RepKeyIndex = WISP_VK_NULL;
		Msg.Msg = WISP_WM_HIT_TEST;
		Msg.HitTest.bKeyDown = bKeyDown;
		Msg.HitTest.HitAreaType = WISP_HIT_WND_NON;
		Msg.HitTest.HitCtrlType = WISP_HIT_CTRL_NON;
		SendMessage(&Msg);
		HitAreaType = Msg.HitTest.HitAreaType;
		HitCtrlType = Msg.HitTest.HitCtrlType;
		Msg.KeyEvent.HitAreaType = HitAreaType;
		Msg.KeyEvent.HitCtrlType = HitCtrlType;
		Msg.KeyEvent.KeyType = KeyType;
		Msg.KeyEvent.bKeyDown = bKeyDown;
		Msg.KeyEvent.ScanCode = ScanCode;
		Msg.Msg = WISP_WM_KEY_EVENT;
		/*
		if(m_KeyHookWndList.Count())
		{
			for(CWndList::IT Iter = m_KeyHookWndList.Begin();Iter!=m_KeyHookWndList.End();Iter++)
			{
				if(*Iter!=Msg.hWnd)
				{
					Msg.hWnd = *Iter;
					SendMessage(&Msg);
				}
			}
		}*/
		Msg.hWnd = pMsgWnd;
		SendMessage(&Msg);
		if(KeyType == WISP_VK_LBUTTON)
		{
			if(pMsgWnd->m_State&WISP_WST_SIZING)
			{
				pMsgWnd->m_State&=~WISP_WST_SIZING;
				ChangeCursorType(WISP_CT_ARROW);
			}
		}
	}
	return true;
}

void CWispBase::StartMouseKeyRep(UINT RepKeyIndex)
{
	if(m_RepKeyIndex==RepKeyIndex)
		return;
	m_RepKeyIndex = RepKeyIndex;
	m_RepKeyElapse = 0;
	m_RepKeyPeriod = WISP_MOUSE_KEY_REPEAT_DELAY;
}

void CWispBase::StopMouseKeyRep()
{
	m_RepKeyIndex = WISP_VK_NULL;
}

void CWispBase::UpdateCursor()
{
	if(m_bHideMouse==false)
	{
		m_pRootWnd->m_pUpdateRect = &m_pRootWnd->m_WindowRect;
		m_pCurDrawObj->DrawCursor(&m_MousePT, &m_pRootWnd->m_WindowDC,m_CursorType,m_pCursorDIB);
		m_pRootWnd->m_pUpdateRect = NULL;
	}
}

int CWispBase::GetMetrics(IN UINT Type)
{
	if(Type>=WISP_SM_COUNT)
		return 0;
	return m_Metrics[Type];
}

void CWispBase::UpdateFrameBuffer()
{
	WISP_RECT Rect;
	WISP_MSG Msg;
	if(m_pRootWnd==NULL)
		return;
	Msg.hWnd=m_pRootWnd;
	if(Msg.hWnd->m_pUpdateRect)
		Rect = *Msg.hWnd->m_pUpdateRect;
	else if(m_bHideMouse)
		goto ExitUpdateFrameBuffer;
	if(m_bHideMouse==false)
	{
		WISP_RECT MouseRC;
		MouseRC.x = m_MousePT.x - m_MouseHotPT.x;
		MouseRC.y = m_MousePT.y - m_MouseHotPT.y;
		MouseRC.cx = m_MouseSize.cx;
		MouseRC.cy = m_MouseSize.cy;
		MergeRect(&MouseRC,&m_LastMouseRect);
		Msg.hWnd->UpdateSelfAndChild(&m_LastMouseRect);
		if(Msg.hWnd->m_pUpdateRect==NULL)
			goto ExitUpdateFrameBuffer;
		Rect = *Msg.hWnd->m_pUpdateRect;
		m_LastMouseRect = MouseRC;
	}
	BeginDraw(&Rect);
	Msg.Msg=WISP_WM_UPDATE;
	SendMessage(&Msg);
	UpdateCursor();
	EndDraw(&Rect);
ExitUpdateFrameBuffer:
	return;
}

void CWispBase::RedrawNextTime()
{
	if(m_bNeedUpdate)
		return;
	m_bNeedUpdate=true;
	if(m_bMsgSleeping)
	{
		m_bMsgSleeping = false;
		WakeUpMsgThread();
	}
}

void CWispBase::SendLanguageChangeNotify(CWispBaseWnd*pParentWnd)
{
	CWispBaseWnd*pChildWnd;
	WISP_MSG Msg;
	if(pParentWnd==NULL)
		pParentWnd=m_pRootWnd;
	Msg.hWnd=pParentWnd;
	Msg.Msg=WISP_WM_COMMAND;
	Msg.Command.CmdID=WISP_CMD_LANGUAGE_CHANGE;
	if(SendMessage(&Msg)==false)
		return;
	pChildWnd=pParentWnd->m_ChildWnd;
	while(pChildWnd)
	{
		SendLanguageChangeNotify(pChildWnd);
		pChildWnd=pChildWnd->m_NextWnd;
	}
	return ;

}

CWispBaseWnd* CWispBase::WindowFromPoint(IN WISP_POINT*pPoint,IN CWispBaseWnd*pParentWnd)
{
	CWispBaseWnd*pChildWnd,*pWnd;
	if(pParentWnd==NULL)
		pParentWnd=m_pRootWnd;
	if(pParentWnd->IsScrPtIn(pPoint)==false)
		return NULL;
	pChildWnd=pParentWnd->m_ChildTopWnd;
	while(pChildWnd)
	{
		if(pChildWnd->m_ShowMode!=WISP_SH_HIDDEN && pChildWnd->m_CtrlType != WISP_CTRL_STATIC_GROUP)
		{//WindowFromPointºöÂÔStaticGroup
			if(pParentWnd->IsScrPtIn(pPoint)&&pChildWnd->IsScrPtIn(pPoint))
			{
				pWnd = WindowFromPoint(pPoint,pChildWnd);
				if((pChildWnd->m_Style & WISP_WS_VIRTUAL)==0)
					return pWnd;
				if(pWnd && pWnd != pChildWnd)
					return pWnd;
			}
		}
		pChildWnd=pChildWnd->m_PrevWnd;
	}
	if(pParentWnd->m_Style & WISP_WS_VIRTUAL)
		return NULL;
	return pParentWnd;
}

void CWispBase::InsertWnd(IN CWispBaseWnd*pParentWnd,IN CWispBaseWnd*pNewWnd)
{
	CWispBaseWnd*pLastWnd;
	if(m_pRootWnd==pNewWnd)
		return;
	if(pParentWnd==NULL)
		pParentWnd=m_pRootWnd;
	pLastWnd=pParentWnd->m_ChildWnd;
	if(pNewWnd->m_Style & WISP_WS_ADV_WND)
		m_WndCount++;
	else
		m_BaseWndCount++;
	if(pLastWnd==NULL)
	{
		pParentWnd->m_ChildTopWnd=pParentWnd->m_ChildWnd=pNewWnd;
		pNewWnd->m_NextWnd=pNewWnd->m_PrevWnd=NULL;
		pNewWnd->m_ParentWnd=pParentWnd;
		return;
	}
	pLastWnd=pParentWnd->m_ChildTopWnd;
	pNewWnd->m_NextWnd=NULL;
	pLastWnd->m_NextWnd=pNewWnd;
	pNewWnd->m_PrevWnd=pLastWnd;
	pNewWnd->m_ParentWnd=pParentWnd;
	pParentWnd->m_ChildTopWnd=pNewWnd;
	if(pParentWnd==m_pRootWnd && pNewWnd!=gpCurWisp->m_pTopMostRootWnd)
		gpCurWisp->m_pTopMostRootWnd->Top(false);
	return;
}

void CWispBase::RemoveWnd(IN CWispBaseWnd*pWnd)
{
	if(m_pRootWnd==pWnd)
	{
		m_pRootWnd = NULL;
		m_bActive = false;
		return;
	}
	if(pWnd->m_PrevWnd)
		pWnd->m_PrevWnd->m_NextWnd=pWnd->m_NextWnd;
	if(pWnd->m_NextWnd)
		pWnd->m_NextWnd->m_PrevWnd=pWnd->m_PrevWnd;
	if(pWnd->m_ParentWnd->m_ChildWnd==pWnd)
		pWnd->m_ParentWnd->m_ChildWnd=pWnd->m_PrevWnd?pWnd->m_PrevWnd:pWnd->m_NextWnd;
	if(pWnd->m_ParentWnd->m_ChildTopWnd==pWnd)
		pWnd->m_ParentWnd->m_ChildTopWnd=pWnd->m_PrevWnd;

	if(pWnd->m_Style & WISP_WS_ADV_WND)
		m_WndCount--;
	else
		m_BaseWndCount--;
}

void CWispBase::RemoveWndMsg(IN CWispBaseWnd*pWnd)
{
	for(int nMsg=0;nMsg<m_MsgQueue.Count();nMsg++)
	{
		if(m_MsgQueue[nMsg].hWnd==pWnd)
			m_MsgQueue[nMsg].hWnd=NULL;
	}
}

void CWispBase::CaptureMouseEvent(IN CWispBaseWnd*pWnd)
{
	m_pMouseEventWnd=pWnd;
}

bool CWispBase::MergeMessage(IN WISP_MSG*pNewMsg,INOUT WISP_MSG*pMergeMsg)
{
	if(pNewMsg->Msg!=pMergeMsg->Msg)
		return false;
	switch(pNewMsg->Msg)
	{
	case WISP_WM_MOUSE_MOVE:
		pMergeMsg->MouseEvent.hWndMouseAt = pNewMsg->MouseEvent.hWndMouseAt;
		pMergeMsg->MouseEvent.DeltaX     += pNewMsg->MouseEvent.DeltaX;
		pMergeMsg->MouseEvent.DeltaY     += pNewMsg->MouseEvent.DeltaY;
		break;
	default:
		return false;
	}
	return true;
}

bool CWispBase::GetMessage(OUT WISP_MSG*pMsg)
{
	if(m_MsgQueue.Count())
	{
		*pMsg=m_MsgQueue[0];
		m_MsgQueue.Remove();
		return true;
	}
	return false;
}

bool CWispBase::SendMessage(IN WISP_MSG*pMsg)
{
	bool bResult;
	if(pMsg->hWnd==NULL)
		return true;
	pMsg->bMsgLBTDown = m_KeyMap[WISP_VK_LBUTTON];
	pMsg->bMsgRBTDown = m_KeyMap[WISP_VK_RBUTTON];
	pMsg->MsgMouseWndPT = pMsg->MsgMouseScrPT = m_MousePT;
	PointToRect(&pMsg->MsgMouseWndPT,&pMsg->hWnd->m_ScrWindowRect);
	pMsg->MsgMouseCltPT = pMsg->MsgMouseWndPT;
	if(pMsg->hWnd->m_Style&WISP_WS_ADV_WND)
		PointToRect(&pMsg->MsgMouseCltPT,&((CWispWnd*)pMsg->hWnd)->m_ClientRect);
	bResult=pMsg->hWnd->MsgProc(pMsg);
	if(m_bMsgSleeping)
	{
		WakeUpMsgThread();
	}
	return bResult;
}

bool CWispBase::PostMessage(IN WISP_MSG*pMsg)
{
	WISP_MSG*pLastMsg;
	if(pMsg->hWnd==NULL)
		return false;
	pMsg->bMsgLBTDown = m_KeyMap[WISP_VK_LBUTTON];
	pMsg->bMsgRBTDown = m_KeyMap[WISP_VK_RBUTTON];
	pMsg->MsgMouseWndPT = pMsg->MsgMouseScrPT = m_MousePT;
	PointToRect(&pMsg->MsgMouseWndPT,&((CWispWnd*)pMsg->hWnd)->m_ScrWindowRect);
	if(m_MsgQueue.Count())
	{
		pLastMsg = &m_MsgQueue[m_MsgQueue.Count()-1];
		if(pLastMsg->hWnd==pMsg->hWnd)
		{
			if(MergeMessage(pMsg,pLastMsg))
			{
				goto ExitPostMessage;
			}
		}
	}
	m_MsgQueue.Append(*pMsg);
ExitPostMessage:
	if(m_bMsgSleeping)
	{
		m_bMsgSleeping = false;
		WakeUpMsgThread();
	}
	return true;
}

bool CWispBase::DispatchMessage(IN WISP_MSG*pMsg)
{
	if(pMsg->hWnd==NULL)
		return false;
	return pMsg->hWnd->MsgProc(pMsg);
}

void CWispBase::DispatchMsg()
{
	WISP_MSG Msg;
	while(m_MsgQueue.Count())
	{
		Msg = m_MsgQueue[0];
		m_MsgQueue.Remove();
		DispatchMessage(&Msg);
	}
}

void CWispBase::DispatchInputMsg()
{
	WISP_INPUT_MSG Msg;
	while(m_InputMsgQueue.Count())
	{
		Msg = m_InputMsgQueue[0];
		m_InputMsgQueue.Remove();
		switch(Msg.InputMsg)
		{
		case WISP_INPUT_KEY_EVENT:
			DispatchKeyEvent(Msg.KeyEvent.KeyType,Msg.KeyEvent.bKeyDown,Msg.KeyEvent.ScanCode);
			break;
		case WISP_INPUT_MOUSE_BT_DB_CLICK:
			DispatchMouseButtonDBClick(Msg.MouseBTDBClick.KeyType);
			break;
		case WISP_INPUT_MOUSE_POS_CHG:
			DispatchMousePosChg(Msg.MousePosChg.PosX,Msg.MousePosChg.PosY);
			break;
		case WISP_INPUT_MOUSE_MOVE:
			DispatchMouseMove(Msg.MouseMove.DeltaX,Msg.MouseMove.DeltaY);
			break;
		case WISP_INPUT_MOUSE_WHEEL:
			DispatchMouseWheel(Msg.MouseWheel.DeltaZ);
			break;
		case WISP_INPUT_TIMER:
			DispatchTimer(Msg.Timer.MilliSec);
			break;
		}
	}
}

void CWispBase::Pump()
{
	m_bActive=true;
	while(m_bActive && PumpCondition())
	{
		EnterCriticalSection();
		DispatchInputMsg();
		DispatchMsg();
		if(m_bActive && m_bNeedUpdate && m_LockRef==0)
		{
			UpdateFrameBuffer();
			m_bNeedUpdate=false;
		}
		LeaveCriticalSection();
		m_bMsgSleeping = true;
		SleepMsgThread();
		m_bMsgSleeping = false;
	}
	EnterCriticalSection();
	UpdateFrameBuffer();
	LeaveCriticalSection();
	m_bActive = false;
}

void CWispBase::BlockPump(CWispBaseWnd*pWnd)
{
	m_ModelLevel++;
	while(m_bActive && pWnd->IsWindow() && pWnd->IsVisible())
	{
		DispatchInputMsg();
		DispatchMsg();
		if(m_bActive && m_bNeedUpdate && m_LockRef==0)
		{
			UpdateFrameBuffer();
			m_bNeedUpdate=false;
		}
		LeaveCriticalSection();
		m_bMsgSleeping=true;
		SleepMsgThread();
		m_bMsgSleeping=false;
		EnterCriticalSection();
	}
	m_ModelLevel--;
}

bool CWispBase::SelectDrawObject(CWispDrawObj*pDrawObj)
{
	if(pDrawObj == m_pCurDrawObj)
	{
		if(m_pCurDrawObj)
		{
			m_pCurDrawObj->Release();
			return m_pCurDrawObj->Init();
		}
		return false;
	}
	if(pDrawObj && pDrawObj->Init()==false)
		return false;
	if(m_pCurDrawObj)
		m_pCurDrawObj->Release();
	m_pCurDrawObj = pDrawObj;
	return true;
}

bool CWispBase::PumpCondition()
{
	if(m_KeyMap[WISP_VK_F12] && m_KeyMap[WISP_VK_CONTROL])
		return false;
	return true;
}

WISP_PSTR CWispBase::GetClipboardString()
{
	return (WISP_PSTR)m_ClipboardString;
}

bool CWispBase::SetClipboardString(WISP_PCSTR String)
{
	m_ClipboardString = String;
	return true;
}

void CWispBase::GetFrameBufferDrawHAL(WISP_FRAME_BUFFER*pFrameBuffer)
{
	switch(pFrameBuffer->Bpp)
	{
	case 4:
		pFrameBuffer->pDrawHAL = &m_DrawHAL4Bit;
		break;
	case 8:
		pFrameBuffer->pDrawHAL = &m_DrawHAL8Bit;
		break;
	case 16:
		pFrameBuffer->pDrawHAL = &m_DrawHAL16Bit;
		break;
	case 24:
		pFrameBuffer->pDrawHAL = &m_DrawHAL24Bit;
		break;
	case 32:
		pFrameBuffer->pDrawHAL = &m_DrawHAL32Bit;
		break;
	default:
		pFrameBuffer->pDrawHAL = &m_NotSupportDrawHAL;
		break;
	}
}

bool CWispBase::SaveScreen(PCSTR FileName)
{
	bool Result;
	CWispDIB Bmp;
	Bmp.m_FrameBuffer = m_FrameBuffer;
	Result = Bmp.Save(FileName);
	STZeroMemory(Bmp);
	return Result;
}

int CWispBase::MsgBox(WISP_CHAR*pText,WISP_CHAR*pCaption,UINT uType,CWispBaseWnd*pParentWnd)
{
	return CWispMsgBox::StaticShowMsgBox(pText,pCaption,uType,pParentWnd);
}

void CWispBase::ReportMsg(IN const WISP_CHAR* Format,...)
{
	return;
}

void*CWispBase::GetScreenBuffer(IN int x,IN int y)
{
	return RT_PVOID(m_FrameBuffer.Buffer,y*m_FrameBuffer.LineDistance+x*m_FrameBuffer.Bpp/8);
}

bool CWispBase::CopyToScreen(WISP_FRAME_BUFFER*pRealScreen,WISP_POINT*pPT,WISP_RECT*pUpdateRect)
{
	WISP_RECT rc,rcClip;
	CWispDrawHAL*pDrawHAL;
	void* Buffer;
	int XOffset,YOffset;
	Buffer=pRealScreen->Buffer;
	if(Buffer==NULL)
		return false;
	if(pPT)
	{
		rc.x=pPT->x;
		rc.y=pPT->y;
	}
	else
	{
		rc.x = CENTER_ALGN(m_FrameBuffer.Width,pRealScreen->Width);
		rc.y = CENTER_ALGN(m_FrameBuffer.Height,pRealScreen->Height);
		MIN_LIMIT(rc.x,0);
		MIN_LIMIT(rc.y,0);
	}
	if(pUpdateRect)
	{
		rc.x+=pUpdateRect->x;
		rc.y+=pUpdateRect->y;
		rc.cx=pUpdateRect->cx;
		rc.cy=pUpdateRect->cy;
	}
	else
	{
		rc.cx=m_FrameBuffer.Width;
		rc.cy=m_FrameBuffer.Height;
	}
	switch(pRealScreen->Bpp)
	{
		case 32:
			pDrawHAL = &m_DrawHAL32Bit;
			break;
		case 24:
			pDrawHAL = &m_DrawHAL24Bit;
			break;
		case 16:
			pDrawHAL = &m_DrawHAL16Bit;
			break;
		case 8:
			pDrawHAL = &m_DrawHAL8Bit;
			break;
		case 4:
			pDrawHAL = &m_DrawHAL4Bit;
			break;
		default:
			pDrawHAL = &m_NotSupportDrawHAL;
			break;
	}
	XOffset = rc.x;
	YOffset = rc.y;
	if(pUpdateRect)
	{
		XOffset-=pUpdateRect->x;
		YOffset-=pUpdateRect->y;
	}
	rcClip.x=0;
	rcClip.y=0;
	rcClip.cx=pRealScreen->Width;
	rcClip.cy=pRealScreen->Height;
	if(ClipRect(&rc,&rcClip)==false)
		return true;
	for(int y=0;y<rc.cy;y++)
	{
		pDrawHAL->Copy32BitPixelTo(RT_PVOID(pRealScreen->Buffer,(rc.y+y)*pRealScreen->LineDistance+rc.x*pRealScreen->Bpp/8),
									RT_PVOID(m_FrameBuffer.Buffer,(rc.y-YOffset+y)*m_FrameBuffer.LineDistance+(rc.x-XOffset)*m_FrameBuffer.Bpp/8),rc.cx);
	}
	return true;
}

WISP_PHYS_FONT_INFO	CWispBase::m_PhysFontInfo[WISP_FONT_COUNT]=
{
	{8,16,"\\Font\\Font8x16.dat","\\Font\\WF8x16.dat"},
	{6,12,"\\Font\\Font6x12.dat","\\Font\\WF6x12.dat"},
	{12,16,"\\Font\\ASCI1216.dat","\\Font\\ASCI1216.dat"},
	{12,16,"\\Font\\EBCD1216.dat","\\Font\\EBCD1216.dat"},
	{12,16,"\\Font\\ANSI1216.dat","\\Font\\ANSI1216.dat"},
};

WISP_CHAR CWispBase::m_VKKeyChar[2][WISP_VK_COUNT*2]=
{
	{
	'\0',	'\0',	// WISP_VK_NULL				0x00
	'\0',	'\0',	// WISP_VK_LBUTTON			0x01
	'\0',	'\0',	// WISP_VK_RBUTTON			0x02
	'\0',	'\0',	// WISP_VK_CANCEL			0x03
	'\0',	'\0',	// WISP_VK_MBUTTON			0x04
	'\0',	'\0',	// WISP_VK_XBUTTON1			0x05
	'\0',	'\0',	// WISP_VK_XBUTTON2			0x06
	'\0',	'\0',	// WISP_VK_KEYBOARD_START	0x07
	0x08,	0x08,	// WISP_VK_BACK				0x08
	'\t',	'\t',	// WISP_VK_TAB				0x09
	'\0',	'\0',	// WISP_VK_0X0A				0x0A
	'\0',	'\0',	// WISP_VK_0X0B				0x0B
	'\0',	'\0',	// WISP_VK_CLEAR			0x0C
	'\n',	'\n',	// WISP_VK_RETURN			0x0D
	'\0',	'\0',	// WISP_VK_0X0E				0x0E
	'\0',	'\0',	// WISP_VK_0X0F				0x0F

	'\0',	'\0',	// WISP_VK_SHIFT			0x10
	'\0',	'\0',	// WISP_VK_CONTROL			0x11
	'\0',	'\0',	// WISP_VK_MENU				0x12
	'\0',	'\0',	// WISP_VK_PAUSE			0x13
	'\0',	'\0',	// WISP_VK_CAPITAL			0x14
	'\0',	'\0',	// WISP_VK_0X15				0x15
	'\0',	'\0',	// WISP_VK_0X16				0x16
	'\0',	'\0',	// WISP_VK_0X17				0x17
	'\0',	'\0',	// WISP_VK_0X18				0x18
	'\0',	'\0',	// WISP_VK_0X19				0x19
	'\0',	'\0',	// WISP_VK_0X1A				0x1A
	'\0',	'\0',	// WISP_VK_ESCAPE			0x1B
	'\0',	'\0',	// WISP_VK_CONVERT			0x1C
	'\0',	'\0',	// WISP_VK_NONCONVERT		0x1D
	'\0',	'\0',	// WISP_VK_ACCEPT			0x1E
	'\0',	'\0',	// WISP_VK_MODECHANGE		0x1F

	0x20,	0x20,	// WISP_VK_SPACE			0x20
	'\0',	'\0',	// WISP_VK_PRIOR			0x21
	'\0',	'\0',	// WISP_VK_NEXT				0x22
	'\0',	'\0',	// WISP_VK_END				0x23
	'\0',	'\0',	// WISP_VK_HOME				0x24
	'\0',	'\0',	// WISP_VK_LEFT				0x25
	'\0',	'\0',	// WISP_VK_UP				0x26
	'\0',	'\0',	// WISP_VK_RIGHT			0x27
	'\0',	'\0',	// WISP_VK_DOWN				0x28
	'\0',	'\0',	// WISP_VK_SELECT			0x29
	'\0',	'\0',	// WISP_VK_PRint			0x2A
	'\0',	'\0',	// WISP_VK_EXECUTE			0x2B
	'\0',	'\0',	// WISP_VK_SNAPSHOT			0x2C
	'\0',	'\0',	// WISP_VK_INSERT			0x2D
	'\0',	'\0',	// WISP_VK_DELETE			0x2E
	'\0',	'\0',	// WISP_VK_HELP				0x2F

	')',	'0',	// WISP_VK_0				0x30
	'!',	'1',	// WISP_VK_1				0x31
	'@',	'2',	// WISP_VK_2				0x32
	'#',	'3',	// WISP_VK_3				0x33
	'$',	'4',	// WISP_VK_4				0x34
	'%',	'5',	// WISP_VK_5				0x35
	'^',	'6',	// WISP_VK_6				0x36
	'&',	'7',	// WISP_VK_7				0x37
	'*',	'8',	// WISP_VK_8				0x38
	'(',	'9',	// WISP_VK_9				0x39
	'\0',	'\0',	// WISP_VK_0X3A				0x3A
	'\0',	'\0',	// WISP_VK_0X3B				0x3B
	'\0',	'\0',	// WISP_VK_0X3C				0x3C
	'\0',	'\0',	// WISP_VK_0X3D				0x3D
	'\0',	'\0',	// WISP_VK_0X3E				0x3E
	'\0',	'\0',	// WISP_VK_0X3F				0x3F

	'\0',	'\0',	// WISP_VK_0X40				0x40
	'A',	'a',	// WISP_VK_A				0x41
	'B',	'b',	// WISP_VK_B				0x42
	'C',	'c',	// WISP_VK_C				0x43
	'D',	'd',	// WISP_VK_D				0x44
	'E',	'e',	// WISP_VK_E				0x45
	'F',	'f',	// WISP_VK_F				0x46
	'G',	'g',	// WISP_VK_G				0x47
	'H',	'h',	// WISP_VK_H				0x48
	'I',	'i',	// WISP_VK_I				0x49
	'J',	'j',	// WISP_VK_J				0x4A
	'K',	'k',	// WISP_VK_K				0x4B
	'L',	'l',	// WISP_VK_L				0x4C
	'M',	'm',	// WISP_VK_M				0x4D
	'N',	'n',	// WISP_VK_N				0x4E
	'O',	'o',	// WISP_VK_O				0x4F

	'P',	'p',	// WISP_VK_P				0x50
	'Q',	'q',	// WISP_VK_Q				0x51
	'R',	'r',	// WISP_VK_R				0x52
	'S',	's',	// WISP_VK_S				0x53
	'T',	't',	// WISP_VK_T				0x54
	'U',	'u',	// WISP_VK_U				0x55
	'V',	'v',	// WISP_VK_V				0x56
	'W',	'w',	// WISP_VK_W				0x57
	'X',	'x',	// WISP_VK_X				0x58
	'Y',	'y',	// WISP_VK_Y				0x59
	'Z',	'z',	// WISP_VK_Z				0x5A
	'\0',	'\0',	// WISP_VK_LWIN				0x5B
	'\0',	'\0',	// WISP_VK_RWIN				0x5C
	'\0',	'\0',	// WISP_VK_APPS				0x5D
	'\0',	'\0',	// WISP_VK_0X5E				0x5E
	'\0',	'\0',	// WISP_VK_SLEEP			0x5F

	'0',	'0',	// WISP_VK_NUMPAD0			0x60
	'1',	'1',	// WISP_VK_NUMPAD1			0x61
	'2',	'2',	// WISP_VK_NUMPAD2			0x62
	'3',	'3',	// WISP_VK_NUMPAD3			0x63
	'4',	'4',	// WISP_VK_NUMPAD4			0x64
	'5',	'5',	// WISP_VK_NUMPAD5			0x65
	'6',	'6',	// WISP_VK_NUMPAD6			0x66
	'7',	'7',	// WISP_VK_NUMPAD7			0x67
	'8',	'8',	// WISP_VK_NUMPAD8			0x68
	'9',	'9',	// WISP_VK_NUMPAD9			0x69
	'*',	'*',	// WISP_VK_MULTIPLY			0x6A
	'+',	'+',	// WISP_VK_ADD				0x6B
	'\\',	'\\',	// WISP_VK_SEPARATOR		0x6C
	'-',	'-',	// WISP_VK_SUBTRACT			0x6D
	'.',	'.',	// WISP_VK_DECIMAL			0x6E
	'/',	'/',	// WISP_VK_DIVIDE			0x6F

	'\0',	'\0',	// WISP_VK_F1				0x70
	'\0',	'\0',	// WISP_VK_F2				0x71
	'\0',	'\0',	// WISP_VK_F3				0x72
	'\0',	'\0',	// WISP_VK_F4				0x73
	'\0',	'\0',	// WISP_VK_F5				0x74
	'\0',	'\0',	// WISP_VK_F6				0x75
	'\0',	'\0',	// WISP_VK_F7				0x76
	'\0',	'\0',	// WISP_VK_F8				0x77
	'\0',	'\0',	// WISP_VK_F9				0x78
	'\0',	'\0',	// WISP_VK_F10				0x79
	'\0',	'\0',	// WISP_VK_F11				0x7A
	'\0',	'\0',	// WISP_VK_F12				0x7B
	'\0',	'\0',	// WISP_VK_F13				0x7C
	'\0',	'\0',	// WISP_VK_F14				0x7D
	'\0',	'\0',	// WISP_VK_F15				0x7E
	'\0',	'\0',	// WISP_VK_F16				0x7F

	'\0',	'\0',	// WISP_VK_F17				0x80
	'\0',	'\0',	// WISP_VK_F18				0x81
	'\0',	'\0',	// WISP_VK_F19				0x82
	'\0',	'\0',	// WISP_VK_F20				0x83
	'\0',	'\0',	// WISP_VK_F21				0x84
	'\0',	'\0',	// WISP_VK_F22				0x85
	'\0',	'\0',	// WISP_VK_F23				0x86
	'\0',	'\0',	// WISP_VK_F24				0x87
	'\0',	'\0',	// WISP_VK_0X88				0x88
	'\0',	'\0',	// WISP_VK_0X89				0x89
	'\0',	'\0',	// WISP_VK_0X8A				0x8A
	'\0',	'\0',	// WISP_VK_0X8B				0x8B
	'\0',	'\0',	// WISP_VK_0X8C				0x8C
	'\0',	'\0',	// WISP_VK_0X8D				0x8D
	'\0',	'\0',	// WISP_VK_0X8E				0x8E
	'\0',	'\0',	// WISP_VK_0X8F				0x8F

	'\0',	'\0',	// WISP_VK_0X90				0x90
	'\0',	'\0',	// WISP_VK_0X91				0x91
	'\0',	'\0',	// WISP_VK_0X92				0x92
	'\0',	'\0',	// WISP_VK_0X93				0x93
	'\0',	'\0',	// WISP_VK_0X94				0x94
	'\0',	'\0',	// WISP_VK_0X95				0x95
	'\0',	'\0',	// WISP_VK_0X96				0x96
	'\0',	'\0',	// WISP_VK_0X97				0x97
	'\0',	'\0',	// WISP_VK_0X98				0x98
	'\0',	'\0',	// WISP_VK_0X99				0x99
	'\0',	'\0',	// WISP_VK_0X9A				0x9A
	'\0',	'\0',	// WISP_VK_0X9B				0x9B
	'\0',	'\0',	// WISP_VK_0X9C				0x9C
	'\0',	'\0',	// WISP_VK_0X9D				0x9D
	'\0',	'\0',	// WISP_VK_0X9E				0x9E
	'\0',	'\0',	// WISP_VK_0X9F				0x9F

	'\0',	'\0',	// WISP_VK_LSHIFT			0xA0
	'\0',	'\0',	// WISP_VK_RSHIFT			0xA1
	'\0',	'\0',	// WISP_VK_LCONTROL			0xA2
	'\0',	'\0',	// WISP_VK_RCONTROL			0xA3
	'\0',	'\0',	// WISP_VK_LMENU			0xA4
	'\0',	'\0',	// WISP_VK_RMENU			0xA5
	'\0',	'\0',	// VK_BROWSER_BACK			0xA6
	'\0',	'\0',	// VK_BROWSER_FORWARD		0xA7
	'\0',	'\0',	// VK_BROWSER_REFRESH		0xA8
	'\0',	'\0',	// VK_BROWSER_STOP			0xA9
	'\0',	'\0',	// VK_BROWSER_SEARCH		0xAA
	'\0',	'\0',	// VK_BROWSER_FAVORITES		0xAB
	'\0',	'\0',	// VK_BROWSER_HOME			0xAC
	'\0',	'\0',	// VK_VOLUME_MUTE			0xAD
	'\0',	'\0',	// VK_VOLUME_DOWN			0xAE
	'\0',	'\0',	// VK_VOLUME_UP				0xAF

	'\0',	'\0',	// VK_MEDIA_NEXT_TRACK		0xB0
	'\0',	'\0',	// VK_MEDIA_PREV_TRACK		0xB1
	'\0',	'\0',	// VK_MEDIA_STOP			0xB2
	'\0',	'\0',	// VK_MEDIA_PLAY_PAUSE		0xB3
	'\0',	'\0',	// VK_LAUNCH_MAIL			0xB4
	'\0',	'\0',	// VK_LAUNCH_MEDIA_SELECT	0xB5
	'\0',	'\0',	// VK_LAUNCH_APP1			0xB6
	'\0',	'\0',	// VK_LAUNCH_APP2			0xB7
	'\0',	'\0',	// WISP_VK_0XB8				0xB8
	'\0',	'\0',	// WISP_VK_0XB9				0xB9
	':',	';',	// WISP_VK_OEM_1			0xBA   // ';:' for US
	'+',	'=',	// WISP_VK_OEM_PLUS			0xBB   // '+' any country
	'<',	',',	// WISP_VK_OEM_COMMA		0xBC   // ',' any country
	'_',	'-',	// WISP_VK_OEM_MINUS		0xBD   // '-' any country
	'>',	'.',	// WISP_VK_OEM_PERIOD		0xBE   // '.' any country
	'?',	'/',	// WISP_VK_OEM_2			0xBF   // '/?' for US

	'~',	'`',	// WISP_VK_OEM_3			0xC0   // '`~' for US
	'\0',	'\0',	// WISP_VK_0XC1				0xC1
	'\0',	'\0',	// WISP_VK_0XC2				0xC2
	'\0',	'\0',	// WISP_VK_0XC3				0xC3
	'\0',	'\0',	// WISP_VK_0XC4				0xC4
	'\0',	'\0',	// WISP_VK_0XC5				0xC5
	'\0',	'\0',	// WISP_VK_0XC6				0xC6
	'\0',	'\0',	// WISP_VK_0XC7				0xC7
	'\0',	'\0',	// WISP_VK_0XC8				0xC8
	'\0',	'\0',	// WISP_VK_0XC9				0xC9
	'\0',	'\0',	// WISP_VK_0XCA				0xCA
	'\0',	'\0',	// WISP_VK_0XCB				0xCB
	'\0',	'\0',	// WISP_VK_0XCC				0xCC
	'\0',	'\0',	// WISP_VK_0XCD				0xCD
	'\0',	'\0',	// WISP_VK_0XCE				0xCE
	'\0',	'\0',	// WISP_VK_0XCF				0xCF

	'\0',	'\0',	// WISP_VK_0XD0				0xD0
	'\0',	'\0',	// WISP_VK_0XD1				0xD1
	'\0',	'\0',	// WISP_VK_0XD2				0xD2
	'\0',	'\0',	// WISP_VK_0XD3				0xD3
	'\0',	'\0',	// WISP_VK_0XD4				0xD4
	'\0',	'\0',	// WISP_VK_0XD5				0xD5
	'\0',	'\0',	// WISP_VK_0XD6				0xD6
	'\0',	'\0',	// WISP_VK_0XD7				0xD7
	'\0',	'\0',	// WISP_VK_0XD8				0xD8
	'\0',	'\0',	// WISP_VK_0XD9				0xD9
	'\0',	'\0',	// WISP_VK_0XDA				0xDA
	'{',	'[',	// WISP_VK_OEM_4			0xDB  //  '[{' for US
	'|',	'\\',	// WISP_VK_OEM_5			0xDC  //  '\|' for US
	'}',	']',	// WISP_VK_OEM_6			0xDD  //  ']}' for US
	'\"',	'\'',	// WISP_VK_OEM_7			0xDE  //  ''"' for US
	'\0',	'\0',	// WISP_VK_OEM_8			0xDF

	'\0',	'\0',	// WISP_VK_0XE0				0xE0
	'\0',	'\0',	// WISP_VK_OEM_AX			0xE1  //  'AX' key on Japanese AX kbd
	'\0',	'\0',	// WISP_VK_OEM_102			0xE2  //  "<>" or "\|" on RT 102-key kbd.
	'\0',	'\0',	// WISP_VK_ICO_HELP			0xE3  //  Help key on ICO
	'\0',	'\0',	// WISP_VK_ICO_00			0xE4  //  00 key on ICO
	'\0',	'\0',	// WISP_VK_PROCESSKEY		0xE5
	'\0',	'\0',	// WISP_VK_ICO_CLEAR		0xE6
	'\0',	'\0',	// WISP_VK_PACKET			0xE7
	'\0',	'\0',	// WISP_VK_OEM_RESET		0xE9
	'\0',	'\0',	// WISP_VK_OEM_JUMP			0xEA
	'\0',	'\0',	// WISP_VK_OEM_PA1			0xEB
	'\0',	'\0',	// WISP_VK_OEM_PA2			0xEC
	'\0',	'\0',	// WISP_VK_OEM_PA3			0xED
	'\0',	'\0',	// WISP_VK_OEM_WSCTRL		0xEE
	'\0',	'\0',	// WISP_VK_OEM_CUSEL		0xEF

	'\0',	'\0',	// WISP_VK_OEM_ATTN			0xF0
	'\0',	'\0',	// WISP_VK_OEM_FINISH		0xF1
	'\0',	'\0',	// WISP_WISP_VK_OEM_COPY	0xF2
	'\0',	'\0',	// WISP_VK_OEM_AUTO			0xF3
	'\0',	'\0',	// WISP_VK_OEM_ENLW			0xF4
	'\0',	'\0',	// WISP_VK_OEM_BACKTAB		0xF5
	'\0',	'\0',	// WISP_VK_VK_ATTN			0xF6
	'\0',	'\0',	// WISP_VK_VK_CRSEL			0xF7
	'\0',	'\0',	// WISP_VK_VK_EXSEL			0xF8
	'\0',	'\0',	// WISP_VK_VK_EREOF			0xF9
	'\0',	'\0',	// WISP_VK_VK_PLAY			0xFA
	'\0',	'\0',	// WISP_VK_VK_ZOOM			0xFB
	'\0',	'\0',	// WISP_VK_VK_NONAME		0xFC
	'\0',	'\0',	// WISP_VK_VK_PA1			0xFD
	'\0',	'\0',	// WISP_VK_VK_OEM_CLEAR		0xFE
	'\0',	'\0',	// WISP_VK_MAX_ID			0xFF
	},
{
	'\0',	'\0',	// WISP_VK_NULL				0x00
	'\0',	'\0',	// WISP_VK_LBUTTON			0x01
	'\0',	'\0',	// WISP_VK_RBUTTON			0x02
	'\0',	'\0',	// WISP_VK_CANCEL			0x03
	'\0',	'\0',	// WISP_VK_MBUTTON			0x04
	'\0',	'\0',	// WISP_VK_XBUTTON1			0x05
	'\0',	'\0',	// WISP_VK_XBUTTON2			0x06
	'\0',	'\0',	// WISP_VK_KEYBOARD_START	0x07
	0x08,	0x08,	// WISP_VK_BACK				0x08
	'\t',	'\t',	// WISP_VK_TAB				0x09
	'\0',	'\0',	// WISP_VK_0X0A				0x0A
	'\0',	'\0',	// WISP_VK_0X0B				0x0B
	'\0',	'\0',	// WISP_VK_CLEAR			0x0C
	'\n',	'\n',	// WISP_VK_RETURN			0x0D
	'\0',	'\0',	// WISP_VK_0X0E				0x0E
	'\0',	'\0',	// WISP_VK_0X0F				0x0F

	'\0',	'\0',	// WISP_VK_SHIFT			0x10
	'\0',	'\0',	// WISP_VK_CONTROL			0x11
	'\0',	'\0',	// WISP_VK_MENU				0x12
	'\0',	'\0',	// WISP_VK_PAUSE			0x13
	'\0',	'\0',	// WISP_VK_CAPITAL			0x14
	'\0',	'\0',	// WISP_VK_0X15				0x15
	'\0',	'\0',	// WISP_VK_0X16				0x16
	'\0',	'\0',	// WISP_VK_0X17				0x17
	'\0',	'\0',	// WISP_VK_0X18				0x18
	'\0',	'\0',	// WISP_VK_0X19				0x19
	'\0',	'\0',	// WISP_VK_0X1A				0x1A
	'\0',	'\0',	// WISP_VK_ESCAPE			0x1B
	'\0',	'\0',	// WISP_VK_CONVERT			0x1C
	'\0',	'\0',	// WISP_VK_NONCONVERT		0x1D
	'\0',	'\0',	// WISP_VK_ACCEPT			0x1E
	'\0',	'\0',	// WISP_VK_MODECHANGE		0x1F

	0x20,	0x20,	// WISP_VK_SPACE			0x20
	'\0',	'\0',	// WISP_VK_PRIOR			0x21
	'\0',	'\0',	// WISP_VK_NEXT				0x22
	'\0',	'\0',	// WISP_VK_END				0x23
	'\0',	'\0',	// WISP_VK_HOME				0x24
	'\0',	'\0',	// WISP_VK_LEFT				0x25
	'\0',	'\0',	// WISP_VK_UP				0x26
	'\0',	'\0',	// WISP_VK_RIGHT			0x27
	'\0',	'\0',	// WISP_VK_DOWN				0x28
	'\0',	'\0',	// WISP_VK_SELECT			0x29
	'\0',	'\0',	// WISP_VK_PRint			0x2A
	'\0',	'\0',	// WISP_VK_EXECUTE			0x2B
	'\0',	'\0',	// WISP_VK_SNAPSHOT			0x2C
	'\0',	'\0',	// WISP_VK_INSERT			0x2D
	'\0',	'\0',	// WISP_VK_DELETE			0x2E
	'\0',	'\0',	// WISP_VK_HELP				0x2F

	'0',	'\xe0',		// WISP_VK_0				0x30
	'1',	'&',		// WISP_VK_1				0x31
	'2',	'\xe9',		// WISP_VK_2				0x32
	'3',	'"',		// WISP_VK_3				0x33
	'4',	'\'',		// WISP_VK_4				0x34
	'5',	'(',		// WISP_VK_5				0x35
	'6',	'-',		// WISP_VK_6				0x36
	'7',	'\xe0',		// WISP_VK_7				0x37
	'8',	'_',		// WISP_VK_8				0x38
	'9',	'\xe7',		// WISP_VK_9				0x39
	
	'\0',	'\0',	// WISP_VK_0X3A				0x3A
	'\0',	'\0',	// WISP_VK_0X3B				0x3B
	'\0',	'\0',	// WISP_VK_0X3C				0x3C
	'\0',	'\0',	// WISP_VK_0X3D				0x3D
	'\0',	'\0',	// WISP_VK_0X3E				0x3E
	'\0',	'\0',	// WISP_VK_0X3F				0x3F

	'\0',	'\0',	// WISP_VK_0X40				0x40
	'A',	'a',	// WISP_VK_A				0x41
	'B',	'b',	// WISP_VK_B				0x42
	'C',	'c',	// WISP_VK_C				0x43
	'D',	'd',	// WISP_VK_D				0x44
	'E',	'e',	// WISP_VK_E				0x45
	'F',	'f',	// WISP_VK_F				0x46
	'G',	'g',	// WISP_VK_G				0x47
	'H',	'h',	// WISP_VK_H				0x48
	'I',	'i',	// WISP_VK_I				0x49
	'J',	'j',	// WISP_VK_J				0x4A
	'K',	'k',	// WISP_VK_K				0x4B
	'L',	'l',	// WISP_VK_L				0x4C
	'M',	'm',	// WISP_VK_M				0x4D
	'N',	'n',	// WISP_VK_N				0x4E
	'O',	'o',	// WISP_VK_O				0x4F

	'P',	'p',	// WISP_VK_P				0x50
	'Q',	'q',	// WISP_VK_Q				0x51
	'R',	'r',	// WISP_VK_R				0x52
	'S',	's',	// WISP_VK_S				0x53
	'T',	't',	// WISP_VK_T				0x54
	'U',	'u',	// WISP_VK_U				0x55
	'V',	'v',	// WISP_VK_V				0x56
	'W',	'w',	// WISP_VK_W				0x57
	'X',	'x',	// WISP_VK_X				0x58
	'Y',	'y',	// WISP_VK_Y				0x59
	'Z',	'z',	// WISP_VK_Z				0x5A
	'\0',	'\0',	// WISP_VK_LWIN				0x5B
	'\0',	'\0',	// WISP_VK_RWIN				0x5C
	'\0',	'\0',	// WISP_VK_APPS				0x5D
	'\0',	'\0',	// WISP_VK_0X5E				0x5E
	'\0',	'\0',	// WISP_VK_SLEEP			0x5F

	'0',	'0',	// WISP_VK_NUMPAD0			0x60
	'1',	'1',	// WISP_VK_NUMPAD1			0x61
	'2',	'2',	// WISP_VK_NUMPAD2			0x62
	'3',	'3',	// WISP_VK_NUMPAD3			0x63
	'4',	'4',	// WISP_VK_NUMPAD4			0x64
	'5',	'5',	// WISP_VK_NUMPAD5			0x65
	'6',	'6',	// WISP_VK_NUMPAD6			0x66
	'7',	'7',	// WISP_VK_NUMPAD7			0x67
	'8',	'8',	// WISP_VK_NUMPAD8			0x68
	'9',	'9',	// WISP_VK_NUMPAD9			0x69
	'*',	'*',	// WISP_VK_MULTIPLY			0x6A
	'+',	'+',	// WISP_VK_ADD				0x6B
	'\\',	'\\',	// WISP_VK_SEPARATOR		0x6C
	'-',	'-',	// WISP_VK_SUBTRACT			0x6D
	'.',	'.',	// WISP_VK_DECIMAL			0x6E
	'/',	'/',	// WISP_VK_DIVIDE			0x6F

	'\0',	'\0',	// WISP_VK_F1				0x70
	'\0',	'\0',	// WISP_VK_F2				0x71
	'\0',	'\0',	// WISP_VK_F3				0x72
	'\0',	'\0',	// WISP_VK_F4				0x73
	'\0',	'\0',	// WISP_VK_F5				0x74
	'\0',	'\0',	// WISP_VK_F6				0x75
	'\0',	'\0',	// WISP_VK_F7				0x76
	'\0',	'\0',	// WISP_VK_F8				0x77
	'\0',	'\0',	// WISP_VK_F9				0x78
	'\0',	'\0',	// WISP_VK_F10				0x79
	'\0',	'\0',	// WISP_VK_F11				0x7A
	'\0',	'\0',	// WISP_VK_F12				0x7B
	'\0',	'\0',	// WISP_VK_F13				0x7C
	'\0',	'\0',	// WISP_VK_F14				0x7D
	'\0',	'\0',	// WISP_VK_F15				0x7E
	'\0',	'\0',	// WISP_VK_F16				0x7F

	'\0',	'\0',	// WISP_VK_F17				0x80
	'\0',	'\0',	// WISP_VK_F18				0x81
	'\0',	'\0',	// WISP_VK_F19				0x82
	'\0',	'\0',	// WISP_VK_F20				0x83
	'\0',	'\0',	// WISP_VK_F21				0x84
	'\0',	'\0',	// WISP_VK_F22				0x85
	'\0',	'\0',	// WISP_VK_F23				0x86
	'\0',	'\0',	// WISP_VK_F24				0x87
	'\0',	'\0',	// WISP_VK_0X88				0x88
	'\0',	'\0',	// WISP_VK_0X89				0x89
	'\0',	'\0',	// WISP_VK_0X8A				0x8A
	'\0',	'\0',	// WISP_VK_0X8B				0x8B
	'\0',	'\0',	// WISP_VK_0X8C				0x8C
	'\0',	'\0',	// WISP_VK_0X8D				0x8D
	'\0',	'\0',	// WISP_VK_0X8E				0x8E
	'\0',	'\0',	// WISP_VK_0X8F				0x8F

	'\0',	'\0',	// WISP_VK_0X90				0x90
	'\0',	'\0',	// WISP_VK_0X91				0x91
	'\0',	'\0',	// WISP_VK_0X92				0x92
	'\0',	'\0',	// WISP_VK_0X93				0x93
	'\0',	'\0',	// WISP_VK_0X94				0x94
	'\0',	'\0',	// WISP_VK_0X95				0x95
	'\0',	'\0',	// WISP_VK_0X96				0x96
	'\0',	'\0',	// WISP_VK_0X97				0x97
	'\0',	'\0',	// WISP_VK_0X98				0x98
	'\0',	'\0',	// WISP_VK_0X99				0x99
	'\0',	'\0',	// WISP_VK_0X9A				0x9A
	'\0',	'\0',	// WISP_VK_0X9B				0x9B
	'\0',	'\0',	// WISP_VK_0X9C				0x9C
	'\0',	'\0',	// WISP_VK_0X9D				0x9D
	'\0',	'\0',	// WISP_VK_0X9E				0x9E
	'\0',	'\0',	// WISP_VK_0X9F				0x9F

	'\0',	'\0',	// WISP_VK_LSHIFT			0xA0
	'\0',	'\0',	// WISP_VK_RSHIFT			0xA1
	'\0',	'\0',	// WISP_VK_LCONTROL			0xA2
	'\0',	'\0',	// WISP_VK_RCONTROL			0xA3
	'\0',	'\0',	// WISP_VK_LMENU			0xA4
	'\0',	'\0',	// WISP_VK_RMENU			0xA5
	'\0',	'\0',	// VK_BROWSER_BACK			0xA6
	'\0',	'\0',	// VK_BROWSER_FORWARD		0xA7
	'\0',	'\0',	// VK_BROWSER_REFRESH		0xA8
	'\0',	'\0',	// VK_BROWSER_STOP			0xA9
	'\0',	'\0',	// VK_BROWSER_SEARCH		0xAA
	'\0',	'\0',	// VK_BROWSER_FAVORITES		0xAB
	'\0',	'\0',	// VK_BROWSER_HOME			0xAC
	'\0',	'\0',	// VK_VOLUME_MUTE			0xAD
	'\0',	'\0',	// VK_VOLUME_DOWN			0xAE
	'\0',	'\0',	// VK_VOLUME_UP				0xAF

	'\0',	'\0',	// VK_MEDIA_NEXT_TRACK		0xB0
	'\0',	'\0',	// VK_MEDIA_PREV_TRACK		0xB1
	'\0',	'\0',	// VK_MEDIA_STOP			0xB2
	'\0',	'\0',	// VK_MEDIA_PLAY_PAUSE		0xB3
	'\0',	'\0',	// VK_LAUNCH_MAIL			0xB4
	'\0',	'\0',	// VK_LAUNCH_MEDIA_SELECT	0xB5
	'\0',	'\0',	// VK_LAUNCH_APP1			0xB6
	'\0',	'\0',	// VK_LAUNCH_APP2			0xB7
	'\0',	'\0',	// WISP_VK_0XB8				0xB8
	'\0',	'\0',	// WISP_VK_0XB9				0xB9
	'?',	',',	// WISP_VK_OEM_1			0xBA   // ';:' for US
	'+',	'=',	// WISP_VK_OEM_PLUS			0xBB   // '+' any country
	'.',	';',	// WISP_VK_OEM_COMMA		0xBC   // ',' any country
	'\xb0',	')',	// WISP_VK_OEM_MINUS		0xBD   // '-' any country
	'/',	':',	// WISP_VK_OEM_PERIOD		0xBE   // '.' any country
	'\xa7',	'!',	// WISP_VK_OEM_2			0xBF   // '/?' for US

	'~',	'`',	// WISP_VK_OEM_3			0xC0   // '`~' for US
	'\0',	'\0',	// WISP_VK_0XC1				0xC1
	'\0',	'\0',	// WISP_VK_0XC2				0xC2
	'\0',	'\0',	// WISP_VK_0XC3				0xC3
	'\0',	'\0',	// WISP_VK_0XC4				0xC4
	'\0',	'\0',	// WISP_VK_0XC5				0xC5
	'\0',	'\0',	// WISP_VK_0XC6				0xC6
	'\0',	'\0',	// WISP_VK_0XC7				0xC7
	'\0',	'\0',	// WISP_VK_0XC8				0xC8
	'\0',	'\0',	// WISP_VK_0XC9				0xC9
	'\0',	'\0',	// WISP_VK_0XCA				0xCA
	'\0',	'\0',	// WISP_VK_0XCB				0xCB
	'\0',	'\0',	// WISP_VK_0XCC				0xCC
	'\0',	'\0',	// WISP_VK_0XCD				0xCD
	'\0',	'\0',	// WISP_VK_0XCE				0xCE
	'\0',	'\0',	// WISP_VK_0XCF				0xCF

	'\0',	'\0',	// WISP_VK_0XD0				0xD0
	'\0',	'\0',	// WISP_VK_0XD1				0xD1
	'\0',	'\0',	// WISP_VK_0XD2				0xD2
	'\0',	'\0',	// WISP_VK_0XD3				0xD3
	'\0',	'\0',	// WISP_VK_0XD4				0xD4
	'\0',	'\0',	// WISP_VK_0XD5				0xD5
	'\0',	'\0',	// WISP_VK_0XD6				0xD6
	'\0',	'\0',	// WISP_VK_0XD7				0xD7
	'\0',	'\0',	// WISP_VK_0XD8				0xD8
	'\0',	'\0',	// WISP_VK_0XD9				0xD9
	'\0',	'\0',	// WISP_VK_0XDA				0xDA
	'\xa8',	'^',	// WISP_VK_OEM_4			0xDB  //  '[{' for US
	'\xb5',	'*',	// WISP_VK_OEM_5			0xDC  //  '\|' for US
	'\xa3',	'$',	// WISP_VK_OEM_6			0xDD  //  ']}' for US
	'%',	'\xf9',	// WISP_VK_OEM_7			0xDE  //  ''"' for US
	'\0',	'\0',	// WISP_VK_OEM_8			0xDF

	'\0',	'\0',	// WISP_VK_0XE0				0xE0
	'\0',	'\0',	// WISP_VK_OEM_AX			0xE1  //  'AX' key on Japanese AX kbd
	'>',	'<',	// WISP_VK_OEM_102			0xE2  //  "<>" or "\|" on RT 102-key kbd.
	'\0',	'\0',	// WISP_VK_ICO_HELP			0xE3  //  Help key on ICO
	'\0',	'\0',	// WISP_VK_ICO_00			0xE4  //  00 key on ICO
	'\0',	'\0',	// WISP_VK_PROCESSKEY		0xE5
	'\0',	'\0',	// WISP_VK_ICO_CLEAR		0xE6
	'\0',	'\0',	// WISP_VK_PACKET			0xE7
	'\0',	'\0',	// WISP_VK_OEM_RESET		0xE9
	'\0',	'\0',	// WISP_VK_OEM_JUMP			0xEA
	'\0',	'\0',	// WISP_VK_OEM_PA1			0xEB
	'\0',	'\0',	// WISP_VK_OEM_PA2			0xEC
	'\0',	'\0',	// WISP_VK_OEM_PA3			0xED
	'\0',	'\0',	// WISP_VK_OEM_WSCTRL		0xEE
	'\0',	'\0',	// WISP_VK_OEM_CUSEL		0xEF

	'\0',	'\0',	// WISP_VK_OEM_ATTN			0xF0
	'\0',	'\0',	// WISP_VK_OEM_FINISH		0xF1
	'\0',	'\0',	// WISP_WISP_VK_OEM_COPY	0xF2
	'\0',	'\0',	// WISP_VK_OEM_AUTO			0xF3
	'\0',	'\0',	// WISP_VK_OEM_ENLW			0xF4
	'\0',	'\0',	// WISP_VK_OEM_BACKTAB		0xF5
	'\0',	'\0',	// WISP_VK_VK_ATTN			0xF6
	'\0',	'\0',	// WISP_VK_VK_CRSEL			0xF7
	'\0',	'\0',	// WISP_VK_VK_EXSEL			0xF8
	'\0',	'\0',	// WISP_VK_VK_EREOF			0xF9
	'\0',	'\0',	// WISP_VK_VK_PLAY			0xFA
	'\0',	'\0',	// WISP_VK_VK_ZOOM			0xFB
	'\0',	'\0',	// WISP_VK_VK_NONAME		0xFC
	'\0',	'\0',	// WISP_VK_VK_PA1			0xFD
	'\0',	'\0',	// WISP_VK_VK_OEM_CLEAR		0xFE
	'\0',	'\0',	// WISP_VK_MAX_ID			0xFF
	},
};

COLORREF CWispBase::m_DefColorPal[256]=
{
	WISP_RGB(0,0,0),
	WISP_RGB(255,255,255),
	WISP_RGB(192,0,0),
	WISP_RGB(255,0,0),
	WISP_RGB(0,192,0),
	WISP_RGB(0,255,128),
	WISP_RGB(0,0,192),
	WISP_RGB(0,128,255),
	WISP_RGB(128,64,64),
	WISP_RGB(200,100,100),
	WISP_RGB(0,192,192),
	WISP_RGB(0,255,255),
	WISP_RGB(128,128,128),
	WISP_RGB(200,200,200),
	WISP_RGB(192,192,0),
	WISP_RGB(255,255,0),
	WISP_RGB(128,64,0),
	WISP_RGB(255,128,0),
	WISP_RGB(0,0,0),
	WISP_RGB(200,200,200),
	WISP_RGB(236,233,216),
	WISP_RGB(0,0,0),
	WISP_RGB(255,255,255),
	WISP_RGB(35,152,200),
	WISP_RGB(80,176,255),
	WISP_RGB(0,128,255),
	WISP_RGB(100,200,250),
	WISP_RGB(0,130,230),
	WISP_RGB(220,220,220),
	WISP_RGB(85,85,85),
	WISP_RGB(170,170,170),
	WISP_RGB(80,230,255),
	WISP_RGB(50,180,230),
	WISP_RGB(0,0,255),
	WISP_RGB(127,157,185),
	WISP_RGB(127,157,185),
	WISP_RGB(28,81,128),
	WISP_RGB(255,255,255),
	WISP_RGB(243,243,239),
	WISP_RGB(226,225,218),
	WISP_RGB(49,105,198),
	WISP_RGB(248,179,48),
	WISP_RGB(255,214,100),
	WISP_RGB(255,255,255),
	WISP_RGB(0,0,0),
	WISP_RGB(0,0,128),
	WISP_RGB(0,0,255),
	WISP_RGB(49,106,197),
	WISP_RGB(180,200,228),
	WISP_RGB(210,230,255),
	WISP_RGB(138,134,122),
	WISP_RGB(120,152,181),
	WISP_RGB(0,255,255),
	WISP_RGB(255,255,255),
	WISP_RGB(33,161,33),
	WISP_RGB(0,0,0),
	WISP_RGB(118,177,229),
	WISP_RGB(180,214,241),
	WISP_RGB(100,146,185),
	WISP_RGB(235,234,219),
	WISP_RGB(255,255,255),
	WISP_RGB(199,197,178),
	WISP_RGB(226,222,205),
	WISP_RGB(214,210,194),
	WISP_RGB(203,199,184),
	WISP_RGB(243,243,243),
	WISP_RGB(248,169,0),
	WISP_RGB(249,198,84),
	WISP_RGB(248,179,31),
	WISP_RGB(171,237,172),
	WISP_RGB(149,233,150),
	WISP_RGB(124,228,126),
	WISP_RGB(102,223,104),
	WISP_RGB(78,218,80),
	WISP_RGB(53,213,56),
	WISP_RGB(40,210,43),
	WISP_RGB(229,151,0),
	WISP_RGB(248,179,48),
	WISP_RGB(253,216,137),
	WISP_RGB(61,149,255),
	WISP_RGB(43,144,255),
	WISP_RGB(0,85,234),
	WISP_RGB(0,70,224),
	WISP_RGB(1,67,207),
	WISP_RGB(0,61,220),
	WISP_RGB(0,29,160),
	WISP_RGB(0,19,140),
	WISP_RGB(123,123,123),
	WISP_RGB(224,232,254),
	WISP_RGB(241,241,241),
	WISP_RGB(231,235,255),
	WISP_RGB(107,121,189),
	WISP_RGB(172,168,153),
	WISP_RGB(241,239,226),
	WISP_RGB(113,111,100),
	WISP_RGB(222,223,216),
	WISP_RGB(165,165,151),
	WISP_RGB(193,194,184),
	WISP_RGB(208,209,201),
	WISP_RGB(180,250,212),
	WISP_RGB(100,200,255),
	WISP_RGB(255,170,170),
	WISP_RGB(0,155,255),
	WISP_RGB(180,40,40),
	WISP_RGB(112,162,243),
	WISP_RGB(197,194,184),
	WISP_RGB(0,255,0),
	WISP_RGB(255,0,255),
	WISP_RGB(250,250,204),
	WISP_RGB(33,162,33),
	WISP_RGB(123,162,231),
	WISP_RGB(99,117,214),
	WISP_RGB(180,177,163),
	WISP_RGB(254,254,255),
	WISP_RGB(240,240,241),
	WISP_RGB(230,234,255),
	WISP_RGB(224,228,249),
	WISP_RGB(210,216,247),
	WISP_RGB(104,120,191),
	WISP_RGB(40,8,12),
	WISP_RGB(139,51,119),
	WISP_RGB(45,24,44),
	WISP_RGB(232,200,232),
	WISP_RGB(248,232,248),
	WISP_RGB(24,8,29),
	WISP_RGB(184,136,200),
	WISP_RGB(216,176,232),
	WISP_RGB(192,152,216),
	WISP_RGB(154,106,200),
	WISP_RGB(216,200,232),
	WISP_RGB(45,44,52),
	WISP_RGB(185,183,200),
	WISP_RGB(108,103,159),
	WISP_RGB(8,8,136),
	WISP_RGB(8,8,87),
	WISP_RGB(8,8,24),
	WISP_RGB(56,56,128),
	WISP_RGB(104,104,184),
	WISP_RGB(168,168,216),
	WISP_RGB(200,200,248),
	WISP_RGB(184,184,216),
	WISP_RGB(200,200,232),
	WISP_RGB(216,216,248),
	WISP_RGB(216,216,232),
	WISP_RGB(232,232,248),
	WISP_RGB(201,202,216),
	WISP_RGB(94,96,116),
	WISP_RGB(146,147,156),
	WISP_RGB(52,56,86),
	WISP_RGB(40,56,152),
	WISP_RGB(119,136,233),
	WISP_RGB(40,56,136),
	WISP_RGB(56,72,152),
	WISP_RGB(72,88,169),
	WISP_RGB(88,104,184),
	WISP_RGB(120,136,216),
	WISP_RGB(136,152,232),
	WISP_RGB(88,104,168),
	WISP_RGB(104,120,184),
	WISP_RGB(122,136,199),
	WISP_RGB(56,72,134),
	WISP_RGB(136,152,209),
	WISP_RGB(171,184,235),
	WISP_RGB(154,164,199),
	WISP_RGB(8,55,185),
	WISP_RGB(16,24,48),
	WISP_RGB(104,120,168),
	WISP_RGB(149,171,234),
	WISP_RGB(122,134,167),
	WISP_RGB(24,56,136),
	WISP_RGB(40,72,154),
	WISP_RGB(80,127,245),
	WISP_RGB(56,88,168),
	WISP_RGB(72,104,185),
	WISP_RGB(88,120,200),
	WISP_RGB(104,136,216),
	WISP_RGB(22,73,184),
	WISP_RGB(22,48,108),
	WISP_RGB(72,92,138),
	WISP_RGB(88,107,152),
	WISP_RGB(41,109,246),
	WISP_RGB(40,72,136),
	WISP_RGB(56,88,152),
	WISP_RGB(72,104,168),
	WISP_RGB(88,120,184),
	WISP_RGB(104,136,200),
	WISP_RGB(120,152,216),
	WISP_RGB(104,120,151),
	WISP_RGB(168,184,216),
	WISP_RGB(200,216,248),
	WISP_RGB(25,40,64),
	WISP_RGB(110,136,179),
	WISP_RGB(56,104,174),
	WISP_RGB(120,152,200),
	WISP_RGB(71,120,187),
	WISP_RGB(82,133,204),
	WISP_RGB(56,89,133),
	WISP_RGB(103,153,222),
	WISP_RGB(180,209,248),
	WISP_RGB(39,89,152),
	WISP_RGB(88,124,168),
	WISP_RGB(55,72,92),
	WISP_RGB(142,177,216),
	WISP_RGB(200,216,232),
	WISP_RGB(79,168,247),
	WISP_RGB(104,153,200),
	WISP_RGB(168,201,232),
	WISP_RGB(182,200,216),
	WISP_RGB(168,184,199),
	WISP_RGB(8,78,135),
	WISP_RGB(40,90,132),
	WISP_RGB(120,168,208),
	WISP_RGB(113,190,248),
	WISP_RGB(216,232,244),
	WISP_RGB(143,209,246),
	WISP_RGB(9,123,179),
	WISP_RGB(71,127,157),
	WISP_RGB(71,171,200),
	WISP_RGB(94,220,248),
	WISP_RGB(17,167,188),
	WISP_RGB(27,205,231),
	WISP_RGB(43,223,248),
	WISP_RGB(133,233,247),
	WISP_RGB(177,239,248),
	WISP_RGB(109,201,206),
	WISP_RGB(46,133,135),
	WISP_RGB(8,24,24),
	WISP_RGB(232,248,248),
	WISP_RGB(20,106,96),
	WISP_RGB(36,146,76),
	WISP_RGB(19,124,30),
	WISP_RGB(229,248,231),
	WISP_RGB(105,174,105),
	WISP_RGB(191,224,189),
	WISP_RGB(66,233,15),
	WISP_RGB(111,191,49),
	WISP_RGB(169,227,110),
	WISP_RGB(217,237,168),
	WISP_RGB(248,248,232),
	WISP_RGB(179,162,79),
	WISP_RGB(248,235,166),
	WISP_RGB(248,242,213),
	WISP_RGB(140,110,17),
	WISP_RGB(222,193,123),
	WISP_RGB(190,129,29),
	WISP_RGB(82,44,31),
	WISP_RGB(242,194,190),
	WISP_RGB(245,84,75),
	WISP_RGB(235,133,129),
	WISP_RGB(24,8,8),
	WISP_RGB(248,232,232),
	WISP_RGB(25,24,24),
	WISP_RGB(248,248,248),
	WISP_RGB(232,232,232),
	WISP_RGB(72,72,72),
	WISP_RGB(8,8,8),
};

