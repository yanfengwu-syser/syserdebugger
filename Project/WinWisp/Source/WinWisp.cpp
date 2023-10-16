#include "StdAfx.h"
#include "WinWisp.h"
#include <shellapi.h> 
#include <shlobj.h>

#define WS_FRAME_WND (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_THICKFRAME|WS_VISIBLE)
#define RESIZE_DELTA	32

#define WM_WISP_UPDATE	WM_USER+0x10

CLocalWispApp*	gpApp;

CWinWisp::CWinWisp()
{
	gpApp = this;
	m_hArrowCursor=
	m_hDragCursor=
	m_hVertResizeCursor=
	m_hHorzResizeCursor=
	m_hLeftLeanCursor=
	m_hRightLeanCursor=NULL;
	m_FrameStyle = WS_FRAME_WND;
	m_FrameStyleEx = 0;
	m_NotifyIconID = 0;
	m_hTrayIcon = NULL;
}

void CWinWisp::RemoveNotifyIcon(UINT IconID)
{
	///从任务栏中删除图标////////////////
	NOTIFYICONDATA tnd;
	tnd.cbSize=sizeof(NOTIFYICONDATA);
	tnd.hWnd=m_hLocalWnd;
	tnd.uID=0;
	if(m_hTrayIcon)
	{
		DestroyIcon(m_hTrayIcon);
		m_hTrayIcon = NULL;
	}
	Shell_NotifyIcon(NIM_DELETE,&tnd);
	///从任务栏中删除图标////////////////
}

void CWinWisp::InsertNotifyIcon(PCSTR szTip,UINT IconID)
{
	///把图标加入任务栏中////////////////
	NOTIFYICONDATA tnd;
	m_NotifyIconID = IconID;
	m_NotifyString = szTip;
	tnd.cbSize=sizeof(NOTIFYICONDATA);
	tnd.hWnd=m_hLocalWnd;
	tnd.uID=0;
	tnd.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage=WM_WISP_NOTIFY_ICON;
	m_hTrayIcon=tnd.hIcon=LoadIcon(m_hLocalInst,MAKEINTRESOURCE(IconID));
	TStrCpy(tnd.szTip,szTip);
	Shell_NotifyIcon(NIM_ADD,&tnd);
	///把图标加入任务栏中///////////////////////
}

void CWinWisp::ModifyNotifyIcon(UINT IconID)
{
	///从任务栏中删除图标////////////////
	NOTIFYICONDATA tnd;
	tnd.cbSize=sizeof(NOTIFYICONDATA);
	tnd.hWnd=m_hLocalWnd;
	tnd.uID=0;
	tnd.uFlags=NIF_ICON;
	if(m_hTrayIcon)
		DestroyIcon(m_hTrayIcon);
	m_hTrayIcon = tnd.hIcon = LoadIcon(m_hLocalInst,MAKEINTRESOURCE(IconID));
	BOOL boolll = Shell_NotifyIcon(NIM_MODIFY,&tnd);
}

bool CWinWisp::CreateFrame(WISP_CHAR*WndName,int Width,int Height,int Bpp)
{
	WNDCLASSEX wcex;
	char szWndName[256];
	HWND hDesktopWnd;
	RECT DesktopWndRect;
	hDesktopWnd = GetDesktopWindow(); 
	GetWindowRect(hDesktopWnd, &DesktopWndRect); 
	m_RealFrameBuffer.Width = DesktopWndRect.right - DesktopWndRect.left;
	m_RealFrameBuffer.Height = DesktopWndRect.bottom - DesktopWndRect.top;
	if(m_hArrowCursor==NULL)
		m_hArrowCursor = LoadCursor(NULL, IDC_ARROW);
	if(m_hDragCursor=NULL)
		m_hDragCursor = LoadCursor(NULL,IDC_SIZENWSE);
	if(m_hVertResizeCursor==NULL)
		m_hVertResizeCursor = LoadCursor(NULL, IDC_SIZENS);
	if(m_hHorzResizeCursor==NULL)
		m_hHorzResizeCursor = LoadCursor(NULL, IDC_SIZEWE);
	if(m_hLeftLeanCursor==NULL)
		m_hLeftLeanCursor = LoadCursor(NULL, IDC_SIZENWSE);
	if(m_hRightLeanCursor==NULL)
		m_hRightLeanCursor = LoadCursor(NULL, IDC_SIZENESW);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= (WNDPROC)CWinWisp::StaticWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_hLocalInst;
	wcex.hIcon			= m_hIcon;
	wcex.hCursor		= m_hArrowCursor;
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "WispWindowClass";
	wcex.hIconSm		= NULL;
	RegisterClassEx(&wcex);
	UnicodeToAnsi(WndName,szWndName,sizeof(szWndName));
	m_hLocalWnd = CreateWindowEx(m_FrameStyleEx,"WispWindowClass",szWndName,m_FrameStyle,CW_USEDEFAULT,CW_USEDEFAULT,Width,Height,NULL,NULL,m_hLocalInst,NULL);
	RECT ClientRC,WindowRC;
	GetClientRect(m_hLocalWnd,&ClientRC);
	GetWindowRect(m_hLocalWnd,&WindowRC);
	m_DeltaWndWidth = (WindowRC.right-WindowRC.left)-(ClientRC.right - ClientRC.left);
	m_DeltaWndHeight = (WindowRC.bottom-WindowRC.top)-(ClientRC.bottom - ClientRC.top);

	if(m_nLocalCmdShow == SW_MAXIMIZE)
	{
		Width = GetSystemMetrics(SM_CXFULLSCREEN);
		Height = GetSystemMetrics(SM_CYFULLSCREEN);
	}
	SetWindowPos(m_hLocalWnd,NULL,
				(GetSystemMetrics(SM_CXFULLSCREEN)-m_DeltaWndWidth-Width)/2,
				(GetSystemMetrics(SM_CYFULLSCREEN)-m_DeltaWndHeight-Height)/2,
				Width+m_DeltaWndWidth,Height+m_DeltaWndHeight,SWP_NOACTIVATE | SWP_NOZORDER);
	if(m_FrameStyle&WS_VISIBLE)
	{
		ShowWindow(m_hLocalWnd, m_nLocalCmdShow);
		UpdateWindow(m_hLocalWnd);
	}
	m_BmpWidth=m_BmpHeight=0;
	m_CurWndHDC = GetDC(m_hLocalWnd);
	m_CurMemHDC = CreateCompatibleDC(m_CurWndHDC);
	AdjustGDIBitmap(Width,Height);
	return true;
}

bool CWinWisp::ResizingFrame(int Width,int Height)
{
	AdjustGDIBitmap(Width,Height);
	return true;
}

bool CWinWisp::ResizeHostFrame(int Width,int Height)
{
	SetWindowPos(m_hLocalWnd,NULL,0,0,Width+m_DeltaWndWidth,Height+m_DeltaWndHeight,SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);
	return true;
}

void CWinWisp::DestroyFrame()
{
	if(m_hArrowCursor!=NULL)
		DestroyCursor(m_hArrowCursor);
	if(m_hDragCursor==NULL)
		DestroyCursor(m_hDragCursor);
	if(m_hVertResizeCursor!=NULL)
		DestroyCursor(m_hVertResizeCursor);
	if(m_hHorzResizeCursor!=NULL)
		DestroyCursor(m_hHorzResizeCursor);
	if(m_hLeftLeanCursor!=NULL)
		DestroyCursor(m_hLeftLeanCursor);
	if(m_hRightLeanCursor!=NULL)
		DestroyCursor(m_hRightLeanCursor);
	DestroyWindow(m_hLocalWnd);
}

void CWinWisp::SetMouseCaptureNotify()
{
	::SetCapture(m_hLocalWnd);
}

void CWinWisp::ReleaseMouseCaptureNotify()
{
	::ReleaseCapture();
}


void CWinWisp::BeginDraw(WISP_RECT*pUpdateRect)
{
	GdiFlush();
}

void CWinWisp::EndDraw(WISP_RECT*pUpdateRect)
{
	if(pUpdateRect==NULL)
		pUpdateRect = &gpCurWisp->m_pRootWnd->m_WindowRect;
	BitBlt(m_CurWndHDC,pUpdateRect->x,pUpdateRect->y,pUpdateRect->cx,pUpdateRect->cy,m_CurMemHDC,pUpdateRect->x,pUpdateRect->y,SRCCOPY);
}

WISP_PSTR CWinWisp::GetClipboardString()
{
	int Length;
	PCSTR szString;
	HANDLE hClipboard;
	if(IsClipboardFormatAvailable(CF_TEXT)==FALSE)
		return m_ClipboardString;
	OpenClipboard(m_hLocalWnd);
	hClipboard = GetClipboardData(CF_TEXT);
	szString =(PCSTR)GlobalLock(hClipboard);
	if(szString==NULL)
	{
		CloseClipboard();
		return m_ClipboardString;
	}
	Length = TStrLen(szString)+1;
	m_ClipboardString.Preallocate(Length);
	Length = AnsiToUnicode(szString,(PWSTR)m_ClipboardString,Length);
	m_ClipboardString.Truncate(Length);
	GlobalUnlock(hClipboard);
	CloseClipboard();
	return CWispBase::GetClipboardString();
}

bool CWinWisp::SetClipboardString(WISP_PCSTR String)
{
	int Length;
	HGLOBAL hMem;
	PSTR pszStr;
	CWispBase::SetClipboardString(String);
	if(OpenClipboard(m_hLocalWnd))
	{
		EmptyClipboard();
		Length = TStrLen(String)+1;
		hMem = GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT,Length*2);
		pszStr=(PSTR)GlobalLock(hMem);
		UnicodeToAnsi(String,pszStr,Length*2);
		GlobalUnlock(hMem);
		SetClipboardData(CF_TEXT,hMem);
		CloseClipboard();
	}
	return true;
}

void CWinWisp::AdjustGDIBitmap(int Width,int Height)
{
	BITMAPINFO	BitMapInfo;
	if(Width<=0 || Height<=0)
		return;
	m_FrameBuffer.Bpp = 32;
	m_FrameBuffer.Width = Width;
	m_FrameBuffer.Height = Height;
	if(	m_BmpWidth<Width || m_BmpHeight<Height || 
		m_BmpWidth-Width>=RESIZE_DELTA || m_BmpHeight-Height>=RESIZE_DELTA)
	{
		if(m_BmpWidth-Width>=RESIZE_DELTA)
			m_BmpWidth=Width;
		else
			m_BmpWidth=Width+RESIZE_DELTA;

		if(m_BmpHeight-Height>=RESIZE_DELTA)
			m_BmpHeight=Height;
		else
			m_BmpHeight=Height+RESIZE_DELTA;

		BitMapInfo.bmiHeader.biBitCount=32;
		BitMapInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		BitMapInfo.bmiHeader.biCompression=BI_RGB;
		BitMapInfo.bmiHeader.biPlanes=1;
		BitMapInfo.bmiHeader.biSizeImage=0;
		BitMapInfo.bmiHeader.biClrUsed=0;
		BitMapInfo.bmiHeader.biClrImportant=0;
		BitMapInfo.bmiHeader.biHeight=-m_BmpHeight;
		BitMapInfo.bmiHeader.biWidth=m_BmpWidth;
		m_hBitmap = CreateDIBSection(NULL,&BitMapInfo,DIB_RGB_COLORS,(void**)&m_FrameBuffer.Buffer,NULL,0);
		CODE_ASSERT(m_hBitmap);
		DeleteObject(SelectObject(m_CurMemHDC,m_hBitmap));
		m_FrameBuffer.LineDistance = m_BmpWidth*(m_FrameBuffer.Bpp/8);
		m_FrameBuffer.BufferSize = m_FrameBuffer.LineDistance*m_BmpHeight;
	}
}

void CWinWisp::ChangeCursor(UINT CursorType,OUT WISP_POINT*pMouseHotPT,OUT WISP_SIZE*pMouseSize,IN CWispDIB*pDIB)
{
	if(m_bHideMouse==false)
	{
		CWispBase::ChangeCursor(CursorType,pMouseHotPT,pMouseSize,pDIB);
		return;
	}
	HICON hCursor;
	switch(CursorType)
	{
	case WISP_CT_ARROW:
		hCursor = m_hArrowCursor;
		break;
	case WISP_CT_DRAG_ARROW:
		hCursor = m_hHorzResizeCursor;
		break;
	case WISP_CT_RESIZE_VERT:
		hCursor = m_hVertResizeCursor;
		break;
	case WISP_CT_RESIZE_HORZ:
		hCursor = m_hHorzResizeCursor;
		break;
	case WISP_CT_RESIZE_LEFT_LEAN:
		hCursor = m_hLeftLeanCursor;
		break;
	case WISP_CT_RESIZE_RIGHT_LEAN:
		hCursor = m_hRightLeanCursor;
		break;
	default:
		return;
	}
	SetClassLong(m_hLocalWnd,GCL_HCURSOR,PTR_TO_NUM(hCursor));
}

void CWinWisp::ChangeHostCursor(IN NUM_PTR CursorData,OUT WISP_POINT*pMouseHotPT,OUT WISP_SIZE*pMouseSize)
{
	ICONINFO IconInfo;
	HICON hCursor = (HICON)CursorData;
	if(GetIconInfo(hCursor,&IconInfo)==FALSE)
		return;
	pMouseHotPT->x = IconInfo.xHotspot;
	pMouseHotPT->y = IconInfo.yHotspot;
	pMouseSize->cx = pMouseSize->cy = 0;
	SetClassLong(m_hLocalWnd,GCL_HCURSOR,PTR_TO_NUM(hCursor));
}

int CWinWisp::WinMainStart(HINSTANCE hInstance,LPSTR lpCmdLine, int nCmdShow)
{
	int Result;
	m_hLocalInst	= hInstance;
	m_nLocalCmdShow	= nCmdShow;
	m_pCmdLine		= lpCmdLine;
	InitializeCriticalSection(&m_CriticalSection);
	Result = 0;
	if(InitInstance()==false)
		goto Exit;
	Pump();
	Result = ExitInstance();
Exit:
	DeleteCriticalSection(&m_CriticalSection);
	return Result;
}

bool CWinWisp::WakeUpMsgThread()
{
	if(m_bMsgSleeping)
	{
		::PostMessage(m_hLocalWnd,WM_WISP_UPDATE,0,0);
	}
	return true;
}

bool CWinWisp::SleepMsgThread()
{
	MSG msg;
	if(::GetMessage(&msg,NULL,0,0)==FALSE)
	{
		m_bActive = false;
		return true;
	}
	::TranslateMessage(&msg);
	::DispatchMessage(&msg);
	return true;
}


#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL	0x020A
#endif

#ifndef GET_WHEEL_DELTA_WPARAM
#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))
#endif

#ifndef WHEEL_DELTA
#define WHEEL_DELTA		120
#endif

bool CWinWisp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int nRepeat,NewCX,NewCY;
	RECT*pRC;
	switch (message)
	{
	case WM_ERASEBKGND:
		if(gpApp->m_pRootWnd)
			gpApp->EndDraw(NULL);
		break;
	case WM_CREATE:
		gpApp->m_TaskBarCreatedMsg = RegisterWindowMessage(TEXT("TaskbarCreated"));
		ShowCursor(gpApp->m_bHideMouse);
		SetTimer(hWnd,0,30,NULL);
		break;
	case WM_LBUTTONDBLCLK:
		if(gpApp->m_pRootWnd)
			gpApp->OnMouseButtonDBClick(WISP_VK_LBUTTON);
		break;
	case WM_RBUTTONDBLCLK:
		if(gpApp->m_pRootWnd)
			gpApp->OnMouseButtonDBClick(WISP_VK_RBUTTON);
		break;
	case WM_LBUTTONDOWN:
		if(gpApp->m_pRootWnd)
			gpApp->OnKeyEvent(WISP_VK_LBUTTON,true);
		break;
	case WM_RBUTTONDOWN:
		if(gpApp->m_pRootWnd)
			gpApp->OnKeyEvent(WISP_VK_RBUTTON,true);
		break;
	case WM_LBUTTONUP:
		if(gpApp->m_pRootWnd)
			gpApp->OnKeyEvent(WISP_VK_LBUTTON,false);
		break;
	case WM_RBUTTONUP:
		if(gpApp->m_pRootWnd)
			gpApp->OnKeyEvent(WISP_VK_RBUTTON,false);
		break;
	case WM_MOUSEWHEEL:
		if(gpApp->m_pRootWnd)
			gpApp->OnMouseWheel((int)GET_WHEEL_DELTA_WPARAM(wParam)/WHEEL_DELTA);
		break;
	case WM_MOUSEMOVE:
		if(gpApp->m_pRootWnd)
			gpApp->OnMousePosChg((short)LOWORD(lParam),(short)HIWORD(lParam));
		break;
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
		if(gpApp->m_pRootWnd)
		{
			nRepeat = LOW_WORD(lParam);
			for(int n=0;n<nRepeat;n++)
				gpApp->OnKeyEvent((UINT)wParam,true,(BYTE)(HIWORD(lParam) & 0xFF));
		}
		break;
	case WM_SYSKEYUP:
	case WM_KEYUP:
		if(gpApp->m_pRootWnd)
		{
			nRepeat = LOW_WORD(lParam);
			for(int n=0;n<nRepeat;n++)
				gpApp->OnKeyEvent((UINT)wParam,false,(BYTE)(HIWORD(lParam) & 0xFF));
		}
		break;
	case WM_ACTIVATE:
		if(gpApp->m_pRootWnd)
			gpApp->EndDraw(NULL);
		break;
	case WM_TIMER:
		gpApp->OnTimer(20);
		break;
	case WM_DESTROY:
		gpApp->m_bActive = false;
		break;
	case WM_NCCALCSIZE:
		if(gpApp->m_pRootWnd && wParam)
		{
			pRC=((NCCALCSIZE_PARAMS*)NUM_TO_PTR(lParam))->rgrc;
			NewCX = pRC->right-pRC->left-gpApp->m_DeltaWndWidth;
			NewCY = pRC->bottom-pRC->top-gpApp->m_DeltaWndHeight;
			if(NewCX>0 && NewCY>0)
			{
				gpApp->EnterCriticalSection();
				gpApp->m_pRootWnd->m_State = WISP_WST_SIZING;
				gpApp->m_pRootWnd->Resize(NewCX,NewCY);
				gpApp->m_pRootWnd->m_State = WISP_WST_NORMAL;
				gpApp->UpdateFrameBuffer();
				gpApp->LeaveCriticalSection();
			}
		}
		return false;
	case WM_WISP_UPDATE:
		return true;
	default:
		if(message == gpApp->m_TaskBarCreatedMsg)
		{
			if(gpApp->m_NotifyIconID)
				gpApp->InsertNotifyIcon(gpApp->m_NotifyString,gpApp->m_NotifyIconID);
			return true;
		}
		return false;
	}
	return true;
}

LRESULT CALLBACK CWinWisp::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(gpApp->WndProc(hWnd,message,wParam,lParam))
		return 0;
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void CWinWisp::EnterCriticalSection()
{
	::EnterCriticalSection(&m_CriticalSection);
}

void CWinWisp::LeaveCriticalSection()
{
	::LeaveCriticalSection(&m_CriticalSection);
}

bool CWinWisp::SelectDirForm(OUT WISP_PSTR szDir,WISP_PCSTR szTitle)
{
	bool Result;
	BROWSEINFOW bi;
	LPITEMIDLIST pidl;
	LPMALLOC pMalloc;
	if(SHGetMalloc(&pMalloc) != NOERROR)
		return false;
	bi.hwndOwner=m_hLocalWnd;
	bi.pidlRoot=NULL;
	bi.pszDisplayName=NULL;
	bi.lpszTitle=szTitle;
	bi.ulFlags=BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn=NULL;
	bi.lParam=0;
	Result = false;
	if((pidl=SHBrowseForFolderW(&bi)) != NULL)
	{
		Result = SHGetPathFromIDListW(pidl, szDir)!=FALSE;
		pMalloc->Free(pidl);
	}
	pMalloc->Release();
	return Result;
}

bool CWinWisp::SelectFileForm(IN WISP_PCSTR szInitDir,WISP_PCSTR szFilter,bool bSave,OUT WISP_PSTR szFileName,int Length)
{
	WCHAR szBuffer[MAX_FN_LEN];
	OPENFILENAMEW OpenFileName;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = m_hLocalInst;
	OpenFileName.hwndOwner = m_hLocalWnd;
	TStrCpy(szBuffer,szFilter);
	for(int n = TStrLen(szBuffer);n>=0;n--)
	{
		if(szBuffer[n]=='|')
			szBuffer[n]=0;
	}
	OpenFileName.lpstrFilter = szBuffer;
	OpenFileName.nMaxFile = Length;
	OpenFileName.lpstrFile = szFileName;
	OpenFileName.lpstrInitialDir = szInitDir;
	*szFileName = 0;
	return GetOpenFileNameW(&OpenFileName)!=FALSE;
}

void CWinWisp::ReportMsg(IN const WISP_CHAR* Format,...)
{
	WCHAR szBuffer[0x200];
	va_list Next;
	va_start(Next,Format);
	TVSPrintf(szBuffer,Format,Next);
	va_end(Next);
	OutputDebugStringW(szBuffer);
}


