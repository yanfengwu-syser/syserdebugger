#ifndef _EXPORT_MODULE_PAGE_H_
#define _EXPORT_MODULE_PAGE_H_

class CExportModulePage : public CWispForm
{
public:
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate);
	DECLARE_WISP_MSG(OnResize);
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnFileListCommand)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnButtonAdd)
	DECLARE_WISP_MSG_EVENT(OnButtonRemove)
	DECLARE_WISP_MSG_EVENT(OnButtonSave)
	DECLARE_WISP_MSG_EVENT(OnButtonReload)
	DECLARE_WISP_MSG_EVENT(OnButtonDefault)
	CExportModulePage();
	CWispStaticGroup*m_pGroup;
	CWispList*	m_pFileList;
	CWispButton*m_pSaveBT;
	CWispButton*m_pReloadBT;
	CWispButton*m_pDefaultBT;
	CWispButton*m_pAddBT;
	CWispButton*m_pRemoveBT;
	CHAR	m_ExpModFileName[MAX_FN_LEN];
	WCHAR	m_szSystemRootDir[MAX_FN_LEN];
	bool	LoadExpModFileList();
	bool	SaveExpModFileList();
	bool	IsListItem(PCWSTR szName);
};

#endif

