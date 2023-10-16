#ifndef _SDS_FILE_PAGE_H_
#define _SDS_FILE_PAGE_H_


class CSDSFilePage : public CWispForm
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
	CSDSFilePage();
	CWispStaticGroup*m_pGroup;
	CWispList*	m_pFileList;
	CWispButton*m_pSaveBT;
	CWispButton*m_pReloadBT;
	CWispButton*m_pDefaultBT;
	CWispButton*m_pAddBT;
	CWispButton*m_pRemoveBT;
	CHAR	m_SDSFileName[MAX_FN_LEN];
	bool	LoadSDSFileList();
	bool	SaveSDSFileList();
};



#endif
