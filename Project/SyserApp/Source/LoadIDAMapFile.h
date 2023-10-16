#ifndef _LOAD_IDAMAP_FILE_H_
#define _LOAD_IDAMAP_FILE_H_

class CLoadIDAMapForm : public CWispForm
{
public:
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate);
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventBrowseMapFile);
	DECLARE_WISP_MSG_EVENT(OnEventBrowseModule);
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnOK);
	CLoadIDAMapForm(){m_pFormRes = m_FormRes;}
	CWispEdit*m_pMapFileNameEdit;
	CWispEdit*m_pFileModuleNameEdit;
	CWispCheckBox*m_pTransSymCheckBox;
	CWispCheckBox*m_pLoadDepSymCheckBox;
	CWispCheckBox*m_pAutoUnloadSymCheckBox;
	char	m_FileModuleName[MAX_FN_LEN];
	char	m_MapFileName[MAX_FN_LEN];
};


#endif  //_LOAD_IDAMAP_FILE_H_
