#ifndef _OPEN_FILE_FORM_H_
#define _OPEN_FILE_FORM_H_

class COpenFileForm : public CWispForm
{
public:
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate);
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventBrowse);
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnOK);
	COpenFileForm(){m_pFormRes = m_FormRes;}
	CWispEdit*m_pFilenameEdit;
	CWispEdit*m_pCmdlineEdit;
	CWispCheckBox*m_pTransSymCheckBox;
	CWispCheckBox*m_pLoadDepSymCheckBox;
	CWispCheckBox*m_pAutoUnloadSymCheckBox;
	char	m_Filename[MAX_FN_LEN];
	char	m_CmdLine[512];
	bool	m_bTransSym;
	bool	m_bLoadDepSym;
	bool	m_bAutoUnloadSym;
};


#endif
