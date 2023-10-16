#ifndef _PLUGIN_LIST_FORM_H_
#define _PLUGIN_LIST_FORM_H_


class CPluginListForm : public CWispForm
{
public:
	CPluginListForm();
	~CPluginListForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	void Popup();
	void UpdateContext();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_EVENT_MAP
public:
	CWispList* m_pPluginList;
};





#endif
