#ifndef _WIN_WISP_INTERFACE_
#define _WIN_WISP_INTERFACE_
 
#include  "WispApp.h"

#define WM_WISP_NOTIFY_ICON	WM_USER+0x100

class CWinWisp : public CWispApp
{
public:
	CWinWisp();
	UINT		m_FrameStyle;
	UINT		m_FrameStyleEx;
	HWND		m_hLocalWnd;
	HINSTANCE	m_hLocalInst;
	HICON		m_hIcon;
	HICON		m_hTrayIcon;
	int			m_nLocalCmdShow;
	PSTR		m_pCmdLine;
	HDC			m_CurWndHDC;
	HDC			m_CurMemHDC;
	HBITMAP		m_hBitmap;
	HICON		m_hArrowCursor;
	HICON		m_hDragCursor;
	HICON		m_hVertResizeCursor;
	HICON		m_hHorzResizeCursor;
	HICON		m_hLeftLeanCursor;
	HICON		m_hRightLeanCursor;
	int			m_DeltaWndWidth;
	int			m_DeltaWndHeight;
	int			m_BmpWidth;
	int			m_BmpHeight;
	CRITICAL_SECTION m_CriticalSection;
	CStrA		m_NotifyString;
	UINT		m_NotifyIconID;
	UINT		m_TaskBarCreatedMsg;
	WISP_FRAME_BUFFER m_RealFrameBuffer;
public:
	bool	CreateFrame(WISP_CHAR*WndName,int Width,int Height,int Bpp);
	bool	ResizingFrame(int Width,int Height);
	bool	ResizeHostFrame(int Width,int Height);
	void	ChangeCursor(UINT CursorType,OUT WISP_POINT*pMouseHotPT,OUT WISP_SIZE*pMouseSize,IN CWispDIB*pDIB = NULL);
	void	ChangeHostCursor(IN NUM_PTR CursorData,OUT WISP_POINT*pMouseHotPT,OUT WISP_SIZE*pMouseSize);
	void	DestroyFrame();
	void	SetMouseCaptureNotify();
	void	ReleaseMouseCaptureNotify();
	void	BeginDraw(WISP_RECT*pUpdateRect);
	void	EndDraw(WISP_RECT*pUpdateRect);
	void	AdjustGDIBitmap(int Width,int Height);
	WISP_PSTR GetClipboardString();
	bool	SetClipboardString(WISP_PCSTR String);
	HICON	LoadWinWispCursor(LPCSTR CursorID,WISP_POINT*pHotPT,WISP_SIZE*pSize);
	int		WinMainStart(HINSTANCE hInstance,LPSTR lpCmdLine,int nCmdShow);
	virtual	bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static	LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void	RemoveNotifyIcon(UINT IconID);
	void	ModifyNotifyIcon(UINT IconID);
	void	InsertNotifyIcon(PCSTR szTip,UINT IconID);
	void	EnterCriticalSection();
	void	LeaveCriticalSection();
	bool	SelectDirForm(OUT WISP_PSTR szDir,WISP_PCSTR szTitle = NULL);
	bool	SelectFileForm(IN WISP_PCSTR szInitDir,WISP_PCSTR szFilter,bool bSave,OUT WISP_PSTR szFileName,int Length);
	void	ReportMsg(IN const WISP_CHAR* Format,...);
	bool	WakeUpMsgThread();
	bool	SleepMsgThread();
};

typedef CWinWisp	CLocalWispApp;

extern CLocalWispApp*	gpApp;

#endif
