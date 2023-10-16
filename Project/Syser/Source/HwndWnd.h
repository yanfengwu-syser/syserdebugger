#ifndef __HWND_WND__H_
#define __HWND_WND__H_
#include "HwndCmd.h"

class CHwndProcessAndThread : public CWispWnd
{
public:
	CHwndProcessAndThread(){};
	~CHwndProcessAndThread(){};
	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClientUpdate)	
	DECLARE_WISP_MSG_EVENT_MAP
	void UpdateContext();
};

class CHwndClassWnd : public CWispWnd
{
public:
	CHwndClassWnd(){};
	~CHwndClassWnd(){};
	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClientUpdate)	
	DECLARE_WISP_MSG_EVENT_MAP

	void UpdateContext();
};

class CHwndStyleWnd : public CWispWnd
{
public:
	CHwndStyleWnd();
	~CHwndStyleWnd();
	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	void UpdateContext();
	CWispList m_StyleList;
	CWispList m_StyleExList;
	CWispStaticStr m_StyleStr;
	CWispStaticStr m_StyleExStr;
};

class CHwndGeneralWnd : public CWispWnd
{
public:
	CHwndGeneralWnd();
	~CHwndGeneralWnd();
	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClientUpdate)	
	DECLARE_WISP_MSG_EVENT_MAP
	void UpdateContext();
};

class CHwndOtherWnd : public CWispWnd
{
public:
	CHwndOtherWnd();
	~CHwndOtherWnd();
	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClientUpdate)	
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnGotoNextHwnd)
	DECLARE_WISP_MSG_CMD(OnGotoPreviousHwnd)
	DECLARE_WISP_MSG_CMD(OnGotoParentHwnd)
	DECLARE_WISP_MSG_CMD(OnGotoChildHwnd)
	DECLARE_WISP_MSG_CMD(OnGotoOwnerHwnd)
	void UpdateContext();
	CWispStaticGroup m_NextGroup;
	CWispStaticGroup m_PreviousGroup;
	CWispStaticGroup m_ParentGroup;
	CWispStaticGroup m_FirstChildGroup;
	CWispStaticGroup m_OnwerGroup;	
	CWispStaticURL m_NextURL;
	CWispStaticURL m_PreviousURL;
	CWispStaticURL m_ParentURL;
	CWispStaticURL m_FirstChildURL;
	CWispStaticURL m_OwnerURL;
	DWORD m_NextHwnd;
	DWORD m_PreviousHwnd;
	DWORD m_ParentHwnd;
	DWORD m_FirstChildHwnd;
	DWORD m_OwnerHwnd;
};

class CHwndPropertyForm : public CWispForm
{
public:
	CHwndPropertyForm();
	~CHwndPropertyForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:	
	void Popup();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnModuleSelectComboxCmd)
	DECLARE_WISP_MSG_CMD(OnTabActiveChange)

public:
	void UpdateContext(DWORD ModuleBase);
	PSYSER_HWND_INFO GetHwndInfo()
	{
		GetHwndInfoByWndStruct(*(void**)&m_HwndInfoAddress,&m_HwndInfo);
		return &m_HwndInfo;
	}
	PSYSER_HWND_CLASS_INFO GetHwndClassInfo()
	{
		GetClassInfoByHwndInfo(&m_HwndInfo,&m_HwndClassInfo);
		return &m_HwndClassInfo;
	}
private:	
	CWispTabWnd *m_pMainTab;
	CHwndGeneralWnd* m_pGeneralWnd;
	CHwndStyleWnd* m_pStyleWnd;	
	CHwndOtherWnd*	m_pOtherWnd;
	CHwndClassWnd* m_pClassWnd;
	CHwndProcessAndThread* m_pProcessAndThread;
	DWORD m_HwndInfoAddress;
	SYSER_HWND_INFO m_HwndInfo;
	SYSER_HWND_CLASS_INFO m_HwndClassInfo;

};

class CHwndListWnd : public CWispList
{
public:
	CHwndListWnd();
	~CHwndListWnd();
	void	Popup();
	void	UpdateContext(HANDLE hItem,DWORD dwOSHwnd);
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventGoto)
	DECLARE_WISP_MSG_EVENT(OnEventPEExplorer)
	DWORD GetWindowHwndHead();
	void	ItemClickNotify(HANDLE hItem,int Col);
public:	
	CWispMenu	m_PopupMenu;
};

#endif //__HWND_WND__H_