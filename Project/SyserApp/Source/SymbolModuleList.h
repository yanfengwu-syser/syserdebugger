#ifndef _SYMBOLMODULELIST_H_
#define _SYMBOLMODULELIST_H_
typedef TMap<CStrA,HANDLE> SYMMODULEMAP;
class CModuleSymbolForm:public CWispForm
{
	CWispButton* m_DelModuleButton;
	CWispButton* m_AddModuleButton;
	CWispList* m_SymModuleListWnd;
public:
	CModuleSymbolForm();
	~CModuleSymbolForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
	bool InsertSymbolModule(const char* SymModuleFullName);
	bool RemoveSymbolModule(const char* SymModuleFullName);
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	//DECLARE_WISP_MSG(OnTimer)
	DECLARE_WISP_MSG_CMD_MAP
	//DECLARE_WISP_MSG_CMD(OnCmdUpdateDownLoadState)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventButtonDelModule)
	DECLARE_WISP_MSG_EVENT(OnEventButtonAddModule)
	SYMMODULEMAP m_SymModuleMap;
};

#endif /* _SYMBOLMODULELIST_H_ */
