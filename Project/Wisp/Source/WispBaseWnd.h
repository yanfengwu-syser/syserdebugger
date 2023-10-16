#ifndef _WISP_BASE_WND_H_
#define _WISP_BASE_WND_H_

#include "WispDC.h"

#define WISP_WS_NORMAL_NO_MAX	(WISP_WS_CAPTION | WISP_WS_BORDER | WISP_WS_BT_CLOSE | WISP_WS_BT_MIN | WISP_WS_SIZABLE)
#define WISP_WS_NORMAL			(WISP_WS_CAPTION | WISP_WS_BORDER | WISP_WS_BT_CLOSE | WISP_WS_BT_MIN | WISP_WS_BT_MAX | WISP_WS_SIZABLE)
#define WISP_WS_FRAME			(WISP_WS_CAPTION | WISP_WS_BORDER | WISP_WS_BT_CLOSE)

///////////////////////////////////////////
//window style
///////////////////////////////////////////
#define WISP_WS_NULL			0x00000000
#define WISP_WS_CAPTION			0x00000001
#define WISP_WS_BORDER			0x00000002
#define WISP_WS_THIN_BORDER		0x00000006
#define WISP_WS_BT_CLOSE		0x00000008
#define WISP_WS_BT_MAX			0x00000010
#define WISP_WS_BT_MIN			0x00000020
#define WISP_WS_BACK_TRANS		0x00000040
#define WISP_WS_SIZABLE			0x00000080
#define WISP_WS_VIRTUAL			0x00000100
#define WISP_WS_DISABLED		0x00000200
#define WISP_WS_MARKED			0x00000400
#define WISP_WS_DEFAULT			0x00000800	//Form缺省焦点控件
#define WISP_WS_ADV_WND			0x00008000	//用于区分WispBaseWnd和WispWnd

///////////////////////////////////////////
//window advance style
///////////////////////////////////////////
#define WISP_WAS_NULL			0x00000000
#define WISP_WAS_AUTO_DELETE	0x00000001
#define WISP_WAS_HELP_TIP		0x00000002
#define WISP_WAS_DRAG_WND		0x00000004
#define WISP_WAS_DISABLE_MSG_CS	0x00000010

///////////////////////////////////////////
//window show mode
///////////////////////////////////////////
enum WISP_SH
{
	WISP_SH_NULL=0,
	WISP_SH_NORMAL,
	WISP_SH_MINSIZE,
	WISP_SH_HIDDEN,
	WISP_SH_MODAL,
	WISP_SH_MODAL_BLOCK
};

#define WISP_TIP_PERIOD		500

class CWispBase;

#define SEND_MSG		m_pWispBase->SendMessage
#define POST_MSG		m_pWispBase->PostMessage
#define SYS_COLOR		m_pWispBase->m_pCurDrawObj->m_crSystem
#define SYS_METRICS		m_pWispBase->m_Metrics

#define WISP_WND_EXIST_FLAG     0x77777777

class CWispBaseWnd
{
public:
	CWispBaseWnd();
	virtual ~CWispBaseWnd();
	CWispBase*		m_pWispBase;
	WISP_CTRL_TYPE	m_CtrlType;
	UINT			m_State;
	WISP_RECT		m_ScrWindowRect;	//窗口区在屏幕中的位置
	WISP_RECT		m_WindowRect;		//窗口区在窗口中的位置
	UINT			m_Style;
	UINT			m_AdvStyle;
	UINT			m_ShowMode;
	CWispString		m_WndText;
	UINT			m_CmdID;			//CmdID不能为0
	CWispDC			m_WindowDC;
	CWispBaseWnd*	m_PrevWnd;
	CWispBaseWnd*	m_NextWnd;
	CWispBaseWnd*	m_ChildWnd;
	CWispBaseWnd*	m_ChildTopWnd;
	CWispBaseWnd*	m_ParentWnd;
	CWispBaseWnd*	m_PrevModalWnd;
	CWispBaseWnd*	m_OwnerWnd;
	void*			m_WndData;
	CWispString		m_HelpTipString;
	WISP_RECT		m_UpdateRect;
	WISP_RECT*		m_pUpdateRect;		//不要随意修改，会造成更新依赖关系混乱
	int				m_LockUpdateRef;
	UINT			m_WndFlag;
public:
	virtual bool	Create(	IN WISP_PCSTR Name,IN int x,IN int y,IN int cx,IN int cy,IN CWispBaseWnd*pParentWnd = NULL,
							IN UINT CmdID = 0,IN UINT Style=WISP_WS_NORMAL,IN UINT ShowMode=WISP_SH_NORMAL);
	virtual bool	Destroy();
	virtual void	RecalcLayout();
	virtual bool	InitWnd();
	virtual	void	SetOwner(CWispBaseWnd*pOwnerWnd);
	virtual bool	SetWindowText(const WISP_CHAR* pString);
	virtual	CWispString&GetWindowText(){return m_WndText;}
	virtual void	Update(IN const WISP_RECT*pRect=NULL);
	virtual bool	IsScrPtIn(WISP_POINT*pPT);//用于测试WindowFromPoint,特殊处理可使子窗口某些部位看作是父传窗口的
	virtual void	OnHide(){}
	virtual void	OnShow(){}
	bool	Create(	IN WISP_PCSTR Name,IN const CWispRect&Rect,IN CWispBaseWnd*pParentWnd = NULL,
					IN UINT CmdID = 0,IN UINT Style=WISP_WS_NORMAL,IN UINT ShowMode=WISP_SH_NORMAL);
	bool	Show(IN UINT ShowMode = WISP_SH_NORMAL);
	void	Top(bool bUpdate=true);
	
	void	UpdateSelfAndChild(IN const WISP_RECT*pRect=NULL,CWispBaseWnd*pExcChildWnd=NULL);
	void	Move(IN int DeltaX,IN int DeltaY,bool bUpdate = true);
	void	MoveToWindow(IN int PosX,IN int PosY,bool bUpdate = true);
	void	MoveToClient(IN int PosX,IN int PosY,bool bUpdate = true);
	void	MoveToScreen(IN int PosX,IN int PosY,bool bUpdate = true);
	bool	Resize(IN int cx,IN int cy,bool bUpdate = true);
	bool	MoveWindowToWindow(IN int x,IN int y,IN int cx,IN int cy,bool bUpdate = true);
	bool	MoveWindowToWindow(IN const WISP_RECT&Rect,bool bUpdate = true);
	bool	MoveWindowToClient(IN int x,IN int y,IN int cx,IN int cy,bool bUpdate = true);
	bool	MoveWindowToClient(IN const WISP_RECT&Rect,bool bUpdate = true);
	void	Center(CWispBaseWnd*pCenterWnd = NULL);
	/////////////////////////////////////////////////////////////////////////////////
	//Timer
	HANDLE	GetTimer(UINT TimerID);
	HANDLE	InsertTimer(UINT TimerID,int Period,UINT UserData=0,void*UserPtr=NULL);
	bool	RemoveTimer(UINT TimerID);
	bool	RemoveTimer(HANDLE hTimer);
	bool	SetTimerData(UINT TimerID,UINT UserData=0,void*UserPtr=NULL);
	bool	SetTimerData(HANDLE hTimer,UINT UserData=0,void*UserPtr=NULL);
	bool	ModifyTimerPeriod(UINT TimerID,int Period);	
	bool	ModifyTimerPeriod(HANDLE hTimer,int Period);
	//Timer
	/////////////////////////////////////////////////////////////////////////////////
	int		MsgBox(WISP_CHAR* pText, WISP_CHAR* pCaption, UINT uType = 0);
	CWispBaseWnd*Focus();
	INLINE bool	IsFocus(){return m_pWispBase->m_pFocusWnd==this;}
	bool	IsTopMostWindow();
	bool	IsWindow();
	bool	IsChildWndOf(CWispBaseWnd*pParentWnd);
	bool	HookKeyEvent();
	bool	HookMouseMoveEvent();
	bool	UnhookKeyEvent();
	bool	UnhookMouseMoveEvent();
	HANDLE	RegisterHotKey(UINT EventID,UINT KeyType,UINT Modifier,UINT Style = WISP_HKS_CHILD_WND);
	bool	UnregisterHotKey(HANDLE	hHotKey);
	bool	EnableWindow(bool bState);
	bool	EnableHelpTip(const WISP_CHAR*pString);
	bool	DisableHelpTip();
	void	AddAdvStyle(UINT Style){m_AdvStyle|=Style;}
	void	RemoveAdvStyle(UINT Style){m_AdvStyle&=~Style;}
public:
	bool	inline	IsMarked(){return (m_Style&WISP_WS_MARKED)!=0;}
	bool	inline	IsDisabled(){return (m_Style&WISP_WS_DISABLED)!=0;}
	bool	inline	IsEnabled(){return (m_Style&WISP_WS_DISABLED)==0;}
public:
	bool	IsVisible();
	bool	SendCmdMsg(UINT CmdMsg,int CmdParam1=0,void*CmdParam2=NULL);
	bool	PostEventMsg(UINT CmdMsg,int CmdParam1=0,void*CmdParam2=NULL);
	void	PostCloseMsg();
	bool	SendCloseMsg();
	void	LockUpdate(){m_LockUpdateRef++;}
	void	UnlockUpdate(){m_LockUpdateRef--;}
public://消息映射
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG(OnGetFocus)
	DECLARE_WISP_MSG(OnLostFocus)
	DECLARE_WISP_MSG(OnMouseEnter)
	DECLARE_WISP_MSG(OnMouseLeave)
	DECLARE_WISP_MSG(OnTimer)
	DECLARE_WISP_MSG(OnBeginMove)
	DECLARE_WISP_MSG(OnKeyEvent)
};

#endif
