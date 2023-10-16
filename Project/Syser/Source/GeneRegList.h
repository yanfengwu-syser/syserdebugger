#ifndef _GENE_REG_LIST_H_
#define _GENE_REG_LIST_H_


enum REG_GENE_INDEX
{
	REG_GENE_EAX=0,
	REG_GENE_EBX,
	REG_GENE_ECX,
	REG_GENE_EDX,
	REG_GENE_ESI,
	REG_GENE_EDI,
	REG_GENE_EBP,
	REG_GENE_ESP,
	REG_GENE_EIP,
	REG_GENE_EFL,
	REG_GENE_CS,
	REG_GENE_DS,
	REG_GENE_ES,
	REG_GENE_FS,
	REG_GENE_GS,
	REG_GENE_SS,
	REG_GENE_AF,
	REG_GENE_CF,
	REG_GENE_DF,
	REG_GENE_IF,
	REG_GENE_OF,
	REG_GENE_PF,
	REG_GENE_SF,
	REG_GENE_ZF,
	REG_GENE_CS_BASE,
	REG_GENE_DS_BASE,
	REG_GENE_ES_BASE,
	REG_GENE_FS_BASE,
	REG_GENE_GS_BASE,
	REG_GENE_SS_BASE,
#ifdef CODE_OS_NT_DRV	
	REG_GENE_GDTR,	
	REG_GENE_IDTR,
	REG_GENE_LDTR,
	REG_GENE_TR,
	REG_GENE_GDTRBASE,	
	REG_GENE_GDTRLIMIT,	
	REG_GENE_IDTRBASE,
	REG_GENE_IDTRLIMIT,
#endif
	REG_GENE_REGCOUNT
};

class CGeneRegList : public CWispList
{
	//typedef bool (CGeneRegList::*REG_HOTKEY_FP)(IN INT RegIndex);

	//class CRegHotKey
	//{
	//public:
	//	UINT m_RegIndex;
	//	REG_HOTKEY_FP m_fpHotKey;
	//	CRegHotKey(){};
	//	CRegHotKey(UINT Index,REG_HOTKEY_FP fpHotKey):m_RegIndex(Index),m_fpHotKey(fpHotKey){};
	//	~CRegHotKey(){}
	//};
	typedef TMap<UINT,UINT> REGHOTKEYMAP;
public:
	CGeneRegList();
	virtual ~CGeneRegList();
public:
	HANDLE		m_hGeneRegItem[REG_GENE_REGCOUNT];
	X86_CPU_REG	m_PrevCPUReg;
	COLORREF	m_ChgColor;
	COLORREF	m_NormalColor;
	HANDLE		m_hLastItem;
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventShowCode)
	DECLARE_WISP_MSG_EVENT(OnEventShowData)
	DECLARE_WISP_MSG_EVENT(OnShowData)
	DECLARE_WISP_MSG_EVENT(OnShowCode)

	void	Popup();
	void	ResetContext();
	void	UpdateContext();
	void UpdateCommentContext(X86_CPU_REG_PTR& pPtr);
	void	RunTraceUpdateContext(DWORD ModifyBitMask,X86_REG_CONTEXT *pReg,DWORD EIP);
	void	RunTraceUpdateCommentContext(X86_REG_CONTEXT *pReg);
	void	UpdateEFlagContext();
	bool	BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	bool	EndEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	void	ItemClickNotify(HANDLE hItem,int Col);
	CWispMenu m_PopupMenu;
	HANDLE m_hMenuShowCode;
	HANDLE m_hMenuShowData;
	int GetCPUIndex()const {return m_nCPUIndex;}
	void SetCPUIndex(int Index) {m_nCPUIndex=Index;}
	void	AttachShortcutKey();
private:
	int	m_nCPUIndex;
	X86_CPU_REG_PTR m_X86RegPtr;
	REGHOTKEYMAP m_HotKeyMap;
};


#endif

