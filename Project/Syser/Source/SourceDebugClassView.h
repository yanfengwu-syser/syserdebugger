#ifndef _SOURCEDEBUGCLASSVIEW_H_
#define _SOURCEDEBUGCLASSVIEW_H_
class CSourceDebugClassViewList;
class CClassViewFindForm : public CWispForm
{
public:
	CClassViewFindForm();
	~CClassViewFindForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnFindTextCmd)
	DECLARE_WISP_MSG_EVENT(OnFindButtonEvent)
public:
	void SetContextList(CSourceDebugClassViewList* pContextList);
	void FindItemByName(WCHAR* Name);
	CWispButton* m_FindButton;
	CWispButton* m_CloseButton;
	CWispEdit* m_FindEdit;
	CSourceDebugClassViewList* m_pContextList;	
};

class CSourceDebugClassViewList : public CWispList
{
public:
	CSourceDebugClassViewList(void){m_CurrentFindItem=NULL;};
	virtual ~CSourceDebugClassViewList(void){}; 
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnFindDlg)
	DECLARE_WISP_MSG_EVENT_MAP
	void FindItemByName(WCHAR* Name);
	CClassViewFindForm m_FindDlg;
	CWispMenu m_PopupMenu;
	HANDLE m_CurrentFindItem;
};



#endif
