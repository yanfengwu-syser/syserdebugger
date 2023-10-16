#ifndef _PE_EXPLORER_FORM_H_
#define _PE_EXPLORER_FORM_H_
class CPEDataDirectoryList:public CWispList
{
public:
	CPEDataDirectoryList();
	~CPEDataDirectoryList();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnMouseDBClick)		
};
class CPEDataDirectoryWnd : public CWispWnd
{
public:
	CPEDataDirectoryWnd();
	~CPEDataDirectoryWnd();
	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	bool InitList();
	CPEDataDirectoryList m_DataDirectoryList;
	HANDLE m_DataDirectoryItem[16];
	bool LoadPEFile(CMemPEFile* pMemPEFile);
};

class CPEExportList:public CWispList
{
public:
	CPEExportList();
	~CPEExportList();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnMouseDBClick)	
};
class CPEExportWnd : public CWispWnd
{
public:
	CPEExportWnd();
	~CPEExportWnd();
	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	bool InitList();
	CPEExportList m_ExportEntryList;
	bool LoadPEFile(CMemPEFile* pMemPEFile);
};

class CPEImportModuleList:public CWispList
{
public:
	CPEImportModuleList();
	~CPEImportModuleList();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnMouseDBClick)	
};
class CPEImportEntryList:public CWispList
{
public:
	CPEImportEntryList();
	~CPEImportEntryList();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnMouseDBClick)	
	//DECLARE_WISP_MSG_EVENT_MAP
	//DECLARE_WISP_MSG_CMD_MAP
};
class CPEImportWnd : public CWispWnd
{
public:
	CPEImportWnd();
	~CPEImportWnd();
	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnModuleSelected)	
	bool InitList();
	CPEImportModuleList m_ImportModuleList;
	CPEImportEntryList m_ImportEntryList;
	CMemPEFile* m_pMemPEFile;
	bool LoadPEFile(CMemPEFile* pMemPEFile);
	DWORD GetModuleBaseByName(char* FileName);

};
class CPERelcationWnd : public CWispWnd
{
public:
	CPERelcationWnd();
	~CPERelcationWnd();
	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	bool InitList();
	CWispList m_RelPageList;
	CWispList m_RelEntryList;
	bool LoadPEFile(CMemPEFile* pMemPEFile);

};
class CPEHeaderWnd : public CWispWnd
{
public:
	CPEHeaderWnd();
	~CPEHeaderWnd();
	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	bool InitPEHeaderList();
	CWispList	m_pPEHeaderList1;
	CWispList	m_pPEHeaderList2;
	bool LoadPEFile(CMemPEFile* pMemPEFile);
	HANDLE m_Item[16];
	HANDLE m_HItem[17];
};
class CPEExplorerForm : public CWispForm
{
public:
	CPEExplorerForm();
	~CPEExplorerForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:	
	void Popup();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnModuleSelectComboxCmd)

public:
	void UpdateContext(DWORD ModuleBase);
	bool SetPEModuleBase(DWORD ModuleBase);
	bool ChangeModule(DWORD BaseAddress);
private:	
	HANDLE m_DataDirectoryItem[16];
	CMemPEFile m_MemPEFile;
	CPEHeaderWnd* m_PEHeaderWnd;
	CWispTabWnd* m_pMainTab;
	CPERelcationWnd* m_PERelcationWnd;
	CPEImportWnd* m_PEImportWnd;
	CPEExportWnd* m_PEExportWnd;
	CPEDataDirectoryWnd* m_DataDirectoryWnd;
	CWispComboBox* m_ModuleSelectList;
};


#endif  //_PE_EXPLORER_FORM_H_

