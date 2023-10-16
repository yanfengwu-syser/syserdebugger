#ifndef _LOADSOURCEFILE_H_
#define _LOADSOURCEFILE_H_
class CLoadSourceFileDlg:public CWispForm
{
public:
	CLoadSourceFileDlg();
	~CLoadSourceFileDlg();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_EVENT(OnSkipButtonEvent)
	DECLARE_WISP_MSG_EVENT(OnSkipAllButtonEvent)
	DECLARE_WISP_MSG_EVENT(OnBrowseButtonEvent)

	bool CreateForm(IN CWispBaseWnd* pParentWnd,IN UINT ShowMode,IN char* FileName);
public:	
	CWispStaticStr* m_DesciptionStr;
	CWispStaticStr* m_FileNameStr;
	CWispButton*m_SkipButton;
	CWispButton*m_SkipAllButton;
	CWispButton*m_BrowseButton;
	WCHAR m_FileName[MAX_FN_LEN];
	char m_szFileName[MAX_FN_LEN];
};
int LoadSourceFileCallBack(IN char* OrgFileName,OUT char* NewFileName);
#endif //_LOADSOURCEFILE_H_