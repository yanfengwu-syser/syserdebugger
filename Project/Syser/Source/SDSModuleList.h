#ifndef _SDS_MODULE_LIST_H_
#define _SDS_MODULE_LIST_H_

class CSDSModuleList : public CWispList
{
public:
	CSDSModuleList();
	~CSDSModuleList();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventRemove)
	DECLARE_WISP_MSG_EVENT(OnEventSetAsActiveModule)
	void	PopupMenu();
	CWispDIB*m_pIconCFile;
	CWispDIB*m_pIconCPPFile;
	CWispDIB*m_pIconHFile;
	CWispDIB*m_pIconModule;
	HANDLE		m_hActiveModule;
	CSDSModule*	m_pActiveSDSModule;
	CWispMenu	m_SDSModulePopupMenu;
	void SetActiveModule(HANDLE hItem);
	void SetActiveModule(CSDSModule* pSDSModule);
	void ItemDBClickNotify(HANDLE hItem,int Col);
	void InsertSymbolModule(CSDSModule*pSDSModule);
	bool RemoveSymbolModule(CSDSModule*pSDSModule);
	void UpdateModuleFileList(HANDLE hModuleItem,CSDSModule*pSDSModule);
	CSDSModule* GetActiveModule()const;
};

#endif
