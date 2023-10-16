#ifndef _WISP_BASE_H_
#define _WISP_BASE_H_

#include "WispConfig.h"
#include "WispDIBLib.h"
#include "WispFont.h"
#include "WispDrawObj.h"
#include "WispDrawHAL.h"

#define WISP_CAPTION_HEIGHT				18
#define WISP_CAPTION_BT_SIZE			16
#define WISP_FONT_FRAME_HEIGHT			18
#define WISP_BORDER_SIZE				4
#define WISP_THIN_BORDER_SIZE			2
#define WISP_DEFAULT_ALPHA				128
#define WISP_FONT_DISTANCE				2
#define WISP_SCROLL_BORDER_SIZE			16
#define WISP_SCROLL_MIN_SLIDE_SIZE		8
#define WISP_MAX_MSG_QUEUE				128
#define WISP_MAX_INPUT_MSG_QUEUE		128
#define WISP_KEY_REPEAT_PERIOD			15
#define WISP_KEY_REPEAT_DELAY			600
#define WISP_MOUSE_KEY_REPEAT_PERIOD	50
#define WISP_MOUSE_KEY_REPEAT_DELAY		500
#define WISP_RESIZE_SPACE				6

#define WISP_TK							WISP_RGB(255,0,255)

typedef TQueue<WISP_INPUT_MSG,WISP_MAX_MSG_QUEUE>	CInputMsgQueue;
typedef TQueue<WISP_MSG,WISP_MAX_INPUT_MSG_QUEUE>	CMsgQueue;
typedef TMap<WISP_TIMER_KEY,WISP_TIMER>				CTimerMap;
typedef TList<CWispBaseWnd*>						CWndList;
typedef TList<WISP_HOTKEY_ITEM>						CHotKeyList;

#define WispReportMsg								gpCurWisp->ReportMsg
#define WispColor(i)								gpCurWisp->m_pCurDrawObj->m_crSystem[i]

#define WispDIB(f,i)								gpCurWisp->m_DIBLib.LoadDIB(f,i)
#define WispDIBList(f,w,h)							gpCurWisp->m_DIBLib.LoadDIBList(f,w,h,0)
#define WispTKDIB(f,i)								gpCurWisp->m_DIBLib.LoadDIB(f,i,WISP_TK)
#define WispTKDIBList(f,w,h)						gpCurWisp->m_DIBLib.LoadDIBList(f,w,h,0,WISP_TK)
#define WispTKDIBListDIB(f,w,h,i)					gpCurWisp->m_DIBLib.LoadDIBList(f,w,h,0,WISP_TK)->GetDIB(i)

class CWispApp;
class CWispBaseWnd;
class CWispWnd;
class CWispFont;
class CWispTipWnd;

class CWispBase
{
	friend class CWispBaseWnd;
	friend class CWispDC;
public:
	CWispBase();
	virtual ~CWispBase();
public:
//////////////////////////////////////////////////////////////////////////////////////////////////
//平台相关接口
	virtual	bool	Init();
	virtual	void	Release();
	//Frame
	virtual bool	CreateFrame(WISP_CHAR*WndName,int Width,int Height,int Bpp)=0;
	virtual void	DestroyFrame()=0;
	virtual bool	ResizeHostFrame(int Width,int Height);
	virtual bool	ResizingFrame(int Width,int Height);
	virtual bool	MoveFrame(int dx,int dy);
	//Mouse Input
	virtual	void	SetMouseCaptureNotify();
	virtual	void	ReleaseMouseCaptureNotify();
	//Msg Thread
	virtual	bool	WakeUpMsgThread();
	virtual	bool	SleepMsgThread();
	virtual void	EnterCriticalSection();
	virtual void	LeaveCriticalSection();
	//GDI
	virtual void	BeginDraw(WISP_RECT*pUpdateRect);
	virtual void	EndDraw(WISP_RECT*pUpdateRect);
	virtual void	ChangeCursor(IN UINT CursorType,OUT WISP_POINT*pMouseHotPT,OUT WISP_SIZE*pMouseSize,IN CWispDIB*pDIB=NULL);
	virtual	void	ChangeHostCursor(IN NUM_PTR CursorData,OUT WISP_POINT*pMouseHotPT,OUT WISP_SIZE*pMouseSize);
	virtual	void	UpdateFrameBuffer();
	virtual void	UpdateCursor();
	//Timer
	virtual bool	InsertTimerNotify(WISP_TIMER*pTimer);
	virtual bool	RemoveTimerNotify(WISP_TIMER*pTimer);
	//Pal
	virtual	COLORREF GetPalColor(int Index);
	virtual	bool	SetPalColor(int Index,COLORREF Color);
	virtual	void	LoadPalette();
//平台相关接口
//////////////////////////////////////////////////////////////////////////////////////////////////
public:
	virtual void	Pump();
	virtual void	BlockPump(CWispBaseWnd*pWnd);
	virtual	bool	PumpCondition();
	virtual	WISP_PSTR GetClipboardString();
	virtual	bool	SetClipboardString(WISP_PCSTR String);
	virtual void	GetFrameBufferDrawHAL(WISP_FRAME_BUFFER*pFrameBuffer);

	virtual	void	DispatchMousePosChg(IN int PosX,IN int PosY);
	virtual	void	OnMousePosChg(IN int PosX,IN int PosY);

	virtual	void	DispatchMouseMove(IN int DeltaX,IN int DeltaY);
	virtual	void	OnMouseMove(IN int DeltaX,IN int DeltaY);

	virtual void	DispatchMouseWheel(IN int DeltaZ);
	virtual	void	OnMouseWheel(IN int DeltaZ);

	virtual void	DispatchMouseButtonDBClick(UINT KeyType);
	virtual void	OnMouseButtonDBClick(UINT KeyType);

	virtual	void	DispatchKeyEvent(IN UINT KeyType,IN bool bKeyDown,IN UINT ScanCode = 0);
	virtual	void	OnKeyEvent(IN UINT KeyType,IN bool bKeyDown,IN UINT ScanCode = 0);

	virtual	void	DispatchTimer(int MilliSec);
	virtual	void	OnTimer(int MilliSec);

	virtual	void	OnFrameBufferBppChg(int Bpp);
	virtual	void	SetMousePos(int x,int y);
	virtual bool	SelectDirForm(OUT WISP_PSTR szDir,WISP_PCSTR szTitle = NULL){return false;}
	virtual bool	SelectFileForm(IN WISP_PCSTR szInitDir,WISP_PCSTR szFilter,bool bSave,OUT WISP_PSTR szFileName,int Length){return false;}
	void			LockUpdate();
	void			UnlockUpdate();
	void			LockKey();
	void			UnlockKey();
	void			LockTimer();
	void			UnlockTimer();
	void			StartMouseKeyRep(UINT RepKeyIndex);
	void			StopMouseKeyRep();
	void			RedrawNextTime();
public:
//////////////////////////////////////////////////////////////////////////////////////////////////
//屏幕转换
	void*			GetScreenBuffer(IN int x,IN int y);
	bool			CopyToScreen(WISP_FRAME_BUFFER*pRealScreen,WISP_POINT*pPT=NULL,WISP_RECT*pUpdateRect=NULL);
	void			AdjustColor();
//屏幕转换
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//消息
public:
	//融合消息
	bool			MergeMessage(IN WISP_MSG*pNewMsg,INOUT WISP_MSG*pMergeMsg);
	//从消息队列中弹出一消息
	bool			GetMessage(OUT WISP_MSG*pMsg);
	//向消息队列发送一消息，直到此消息被响应才返回。
	bool			SendMessage(IN WISP_MSG*pMsg);
	//向消息队列发送一消息，立即返回。
	bool			PostMessage(IN WISP_MSG*pMsg);
	//派发消息
	bool			DispatchMessage(IN WISP_MSG*pMsg);
	void			DispatchMsg();
	void			DispatchInputMsg();

	bool			SelectDrawObject(CWispDrawObj*pDrawObj);
	bool			m_bActive;
	bool			m_bMsgSleeping;
	CWispDrawObj*	m_pCurDrawObj;
	CWispDrawObj	m_DefDrawObj;
	CWispDIBDrawObj	m_DIBDrawObj;
	CWispDrawHAL	m_NotSupportDrawHAL;
	CWispDraw32Bit	m_DrawHAL32Bit;
	CWispDraw24Bit	m_DrawHAL24Bit;
	CWispDraw16Bit	m_DrawHAL16Bit;
	CWispDraw8Bit	m_DrawHAL8Bit;
	CWispDraw4Bit	m_DrawHAL4Bit;
//消息
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//输入
public:
	CWispString		m_ClipboardString;
	bool			m_KeyMap[WISP_VK_COUNT];
	bool			m_LockMap[WISP_VK_LOCK_COUNT];
	WISP_POINT		m_MousePT;
	WISP_POINT		m_PrevMousePT;
	WISP_POINT		m_MouseHotPT;
	WISP_SIZE		m_MouseSize;
	WISP_RECT		m_LastMouseRect;
	UINT			m_LastMouseClickHitAreaType;
	UINT			m_LastMouseClickHitCtrlType;
	bool			m_bUpdate;
	int				m_LockRef;
	UINT			m_CursorType;
	UINT			m_CursorTypeBak;
	CWispDIB*		m_pCursorDIB;
	CWispDIB*		m_pCursorDIBBak;
	int				m_ModelLevel;
	CWispDIB*		GetDefDIB(IN UINT ID);
	void			ChangeCursorType(IN UINT DIBID);
	void			ChangeCursorType(IN CWispDIB*pDIB);
	void			ChangeHostCursorType(IN NUM_PTR CursorData);
	void			RestorCursorType();
private:
	void			ProcessRepeatKeyEvent();
	bool			OnProcessKeyEvent(IN UINT KeyType,IN bool bKeyDown,IN UINT ScanCode);
	bool			OnProcessMouseKeyEvent(IN UINT KeyType,IN bool bKeyDown,IN UINT ScanCode);
	WISP_CHAR		IsCharKey(IN UINT KeyType);
//输入
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//其它
public:
	bool			SaveScreen(PCSTR FileName);
	int				MsgBox(WISP_CHAR* pText, WISP_CHAR* pCaption, UINT uType = 0,CWispBaseWnd* pParentWnd = NULL);
public:
	bool			KeySimulateMouse(IN UINT KeyType,IN bool bKeyDown);
	void			PrintWispParam();
	virtual void	ReportMsg(IN const WISP_CHAR* Format,...);
//其它
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//窗口管理
public:
	CWispWnd*		m_pRootWnd;
	CWispWnd*		m_pTopMostRootWnd;
	CWispTipWnd*	m_pHelpTipWnd;
	void			InsertWnd(IN CWispBaseWnd*pParentWnd,IN CWispBaseWnd*pNewWnd);
	void			RemoveWnd(IN CWispBaseWnd*pWnd);
	void			RemoveWndMsg(IN CWispBaseWnd*pWnd);
	void			CaptureMouseEvent(IN CWispBaseWnd*pWnd);
	CWispBaseWnd*	WindowFromPoint(IN WISP_POINT*pPoint,IN CWispBaseWnd*pParentWnd = NULL);
	void			SendLanguageChangeNotify(CWispBaseWnd*pParentWnd=NULL);
	virtual int		GetMetrics(IN UINT Type);
	void			BeginMoveWnd(CWispBaseWnd*pWnd=NULL);
	void			EndMoveWnd();
	void			SetKeyboardLayer(int nLayer){m_iKeyboardLayer=nLayer;};
public:
	char			m_CurDir[MAX_FN_LEN];
	PCSTR			m_pszDiskList;
	CWispBaseWnd*	m_pMoveWnd;
	CWispBaseWnd*	m_pDragWnd;
	WISP_POINT		m_BeginPT;
	CPFSFileIO		m_PFSFileIO;
	CWispFont		m_FontList[WISP_FONT_COUNT];
	CWispBaseWnd*	m_pMouseEventWnd;
	CWispBaseWnd*	m_pFocusWnd;
	CWispBaseWnd*	m_pModalWnd;
	CWispDIB		m_DefDIB[WISP_DI_COUNT];
	CWispDIBLib		m_DIBLib;
	int				m_Metrics[WISP_SM_COUNT];				//系统尺寸
	WISP_FRAME_BUFFER	m_FrameBuffer;
	CInputMsgQueue	m_InputMsgQueue;
	CMsgQueue		m_MsgQueue;
	CTimerMap		m_TimerMap;
	CHotKeyList		m_HotKeyList;
	bool			m_bNeedUpdate;
	bool			m_bOldNeedUpdate;
	COLORREF		m_PalColors[256];
	UINT			m_RepKeyIndex;
	int				m_RepKeyElapse;
	int				m_RepKeyPeriod;
	UINT			m_ModKeyState;
public:
	CWndList		m_KeyHookWndList;
	CWndList		m_MouseMoveHookWndList;
	bool			m_KeySimulateMouse;
	bool			m_bHideMouse;
	int				m_KeySimDelta;
	int				m_BaseWndCount;
	int				m_WndCount;
	int				m_KeyLockRef;
	int				m_TimerRef;
	int				m_DefaultFontType;
	int				m_iKeyboardLayer;
//窗口管理
//////////////////////////////////////////////////////////////////////////////////////////////////
public:
	static WISP_PHYS_FONT_INFO	m_PhysFontInfo[WISP_FONT_COUNT];
	static COLORREF		m_DefColorPal[256];
	static WISP_CHAR	m_VKKeyChar[2][WISP_VK_COUNT*2];
};

extern CWispBase*		gpCurWisp;

#endif
