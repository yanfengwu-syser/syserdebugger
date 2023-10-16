#ifndef _GUI_COLOR_PAGE_H_
#define _GUI_COLOR_PAGE_H_

enum COLOR_DEMO_INDEX
{
	COLOR_DEMO_MONITOR = 0,
	COLOR_DEMO_CODE_VIEW,
	COLOR_DEMO_SOURCE_CODE_VIEW,
	MAX_COLOR_DEMO,
};

class CGUIColorPage : public CWispOptionForm
{
	typedef void (CGUIColorPage::*FPGUIColorSimMothed)();
public:
	CGUIColorPage();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG(OnSize)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnUpdateClient)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG(OnListCmd)
	void OptionApplyNotify();
	bool OptionBeforeDefaultNotify();
	void OptionDefaultNotify();
	void OnModify(HANDLE hItem);
	void OptionRestoreNotify();
	int	m_DemoHeight;
	COLOR_DEMO_INDEX	m_CurMothed;
	CWispDIB	m_DemoDIB;
	CWispStaticGroup	m_DemoGroup;
	void DrawMonitorDemo();
	void DrawCodeViewDemo();
	void DrawSourceCodeViewDemo();
	static FPGUIColorSimMothed	m_Mothed[MAX_COLOR_DEMO];
};



#endif
