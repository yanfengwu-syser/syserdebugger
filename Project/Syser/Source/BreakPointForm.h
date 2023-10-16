#ifndef _BREAK_POINT_FORM_H_
#define _BREAK_POINT_FORM_H_

class CBreakPointForm : public CWispForm
{
public:
	CBreakPointForm();
	~CBreakPointForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	CWispList*	m_pCodeBPList;
	CWispList*	m_pDataBPList;
	CWispList*	m_pActiveBPList;
	CWispTabWnd*m_pBPTab;
	CWispButton*m_pBTEdit;
	CWispButton*m_pBTRemove;
	CWispButton*m_pBTRemoveAll;
	CWispButton*m_pBTEnableAll;
	CWispButton*m_pBTDisableAll;
	void Popup();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEdit)
	DECLARE_WISP_MSG_EVENT(OnNew)
	DECLARE_WISP_MSG_EVENT(OnRemove)
	DECLARE_WISP_MSG_EVENT(OnRemoveAll)
	DECLARE_WISP_MSG_EVENT(OnEnableAll)
	DECLARE_WISP_MSG_EVENT(OnDisableAll)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnBPListChange)
	DECLARE_WISP_MSG_CMD(OnBPListItemSelect);
public:
	int		ListCodeBreakPoint();
	int		ListDataBreakPoint();
	int		RefreshCodeBreakPoint();
	int		RefreshDataBreakPoint();
	void	UpdateBPListButton();
	void	UpdateContext();
private:
	void	InitBPList(CWispList*pList);
	void	InitBPItem(CWispList*pList,HANDLE hItem,BREAK_POINT*pBP);
	void	InitModuleBPItem(CWispList*pList,HANDLE hItem,MODULE_BP*pBP);
};


#endif

