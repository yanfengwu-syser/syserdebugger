#ifndef _CODE_VIEW_H_
#define _CODE_VIEW_H_

#include "SyserUI.h"

#define CV_WS_RANGE_SCROLL	0x8000000

typedef TList<ULPOS> ADDRESSNAVIGATIONLIST;
typedef TList<ULPOS> CROSSREFERENCELIST;

#define MAX_JMP_LINE_COUNT		5
#define MAX_POS_LIST_COUNT		100

struct NEAR_JMP_ENRTY
{
	ULPOS	StartAddr;
	ULPOS	EndAddr;
	int		StartLine;
	int		EndLine;
};

enum
{
	ITEM_STATE = 0,
	ITEM_ADDRESS,
	ITEM_BIN_DATA,
	ITEM_ASM_CODE,
	ITEM_COMMENT,
	ITEM_MAX_COUNT
};

enum CODE_VIEW_ADDR_MOD
{
	CODE_VIEW_ADDRESS_MOD = 0,
	CODE_VIEW_OFFSET_MOD,
	CODE_VIEW_REL_TO_EIP_MOD,
};


class CCodeView : public CWispList
{
	//typedef bool (CCodeView::*DATA_HOTKEY_FP)(IN UINT Index);

	//class CCodeHotKey
	//{
	//public:
	//	UINT m_ViewIndex;
	//	DATA_HOTKEY_FP m_fpHotKey;
	//	CCodeHotKey(){};
	//	CCodeHotKey(UINT Index,DATA_HOTKEY_FP fpHotKey):m_ViewIndex(Index),m_fpHotKey(fpHotKey){};
	//	~CCodeHotKey(){}
	//};

	typedef TMap<UINT,UINT> CODEHOTKEYMAP;
public:
	CCodeView();
	~CCodeView();
	typedef TList<ULPOS>	CAddrList;
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnScrollEvent)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnChar)
	DECLARE_WISP_MSG(OnSize)
	DECLARE_WISP_MSG(OnGetFocus)
	DECLARE_WISP_MSG(OnMouseDBClick)
	DECLARE_WISP_MSG(OnUpdateClient)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG(OnCmdVSlide)
	DECLARE_WISP_MSG(OnCmdStringGoto)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventCopy)
	DECLARE_WISP_MSG_EVENT(OnEventFMAutomiatic)
	DECLARE_WISP_MSG_EVENT(OnEventFMSystemExplorer)
	DECLARE_WISP_MSG_EVENT(OnEventFMSourceCodeExplorer)
	DECLARE_WISP_MSG_EVENT(OnEventAddressModeHex)
	DECLARE_WISP_MSG_EVENT(OnEventOffsetModeHex)
	DECLARE_WISP_MSG_EVENT(OnEventRelativeToEIP)
	DECLARE_WISP_MSG_EVENT(OnEventCrossReference)
	DECLARE_WISP_MSG_EVENT(OnEventXrefOperand)
	DECLARE_WISP_MSG_EVENT(OnEventToggleBreakPoint)
	DECLARE_WISP_MSG_EVENT(OnEventToggleBreakPointState)
	DECLARE_WISP_MSG_EVENT(OnEventToggleBookMarks);
	DECLARE_WISP_MSG_EVENT(OnEventGotoHere)
	DECLARE_WISP_MSG_EVENT(OnEventNextPos)
	DECLARE_WISP_MSG_EVENT(OnEventPrevPos)
	DECLARE_WISP_MSG_EVENT(OnEventSavePos)
	DECLARE_WISP_MSG_EVENT(OnEventEmptyPosList)
	//DECLARE_WISP_MSG_EVENT(OnEventAnalyzeFromAddress)
	DECLARE_WISP_MSG_EVENT(OnEventToggleSymbol)
	DECLARE_WISP_MSG_EVENT(OnEventToggleFullSymbol)
	DECLARE_WISP_MSG_EVENT(OnEventEnterComment)
	DECLARE_WISP_MSG_EVENT(OnEventStringReference)
	DECLARE_WISP_MSG_EVENT(OnEventEditCode)
	DECLARE_WISP_MSG_EVENT(OnGetNextTrace)
	DECLARE_WISP_MSG_EVENT(OnGetPrevTrace)
	DECLARE_WISP_MSG_EVENT(OnPrevPos)
	DECLARE_WISP_MSG_EVENT(OnNextPos)
	DECLARE_WISP_MSG_EVENT(OnSavePos)
	DECLARE_WISP_MSG_EVENT(OnEnterAddr)
	DECLARE_WISP_MSG_EVENT(OnStartAddressInc)
	DECLARE_WISP_MSG_EVENT(OnStartAddressDec)
	DECLARE_WISP_MSG_EVENT(OnActiveCodeView)

public:

	bool	OnDispatchShortcatKey(IN UINT Index,IN WISP_MSG*pMsg);
	bool	OnActiveCodeView(IN UINT Index);
	void	ItemClickNotify(HANDLE hItem,int Col);
	void	ItemRClickNotify(HANDLE hItem,int Col);
	bool	BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	bool	EndEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	void	SetStartAddress(ULPOS Address,bool bRecordAddr=false);
	void	CenterVisibleAddress(ULPOS Address);
	void	GetCodeRange(DWORD*pStart,DWORD*pEnd);
	bool	BuildASM(HANDLE hItem,CWispString& String);
	bool	UpdateView();
	void	UpdateViewAPICall(ULPOS Address,PCSTR szAPIName,HANDLE hItem,int nLine);
	void	OnPrevPos();
	void	OnNextPos();
	void	OnSavePos();
	void	EmptyPosList();
	void	EnterAddr();
	void	PopupMenu(IN WISP_MSG*pMsg);

	void	SetSelectItemByAddress(ULPOS Address);
	void	GetAddressString(ULPOS Address,WISP_PSTR szBuffer);
	int		GetCrossReferenceList(DWORD Address,CROSSREFERENCELIST* pCrossReferenceList);
	int		GetDataReferenceList(DWORD Address,CROSSREFERENCELIST* pList,DWORD* VarAddr);
	bool	CrossReferenceByAddr(ULPOS Address);
	bool	XrefOperandByAddr(ULPOS Address);
	void	UpdateCodeViewAddrSym();
	void	RecordCurAddr(ULPOS Address,ULPOS PrevAddress);
	void	ToggleHighlight(IN WISP_MSG* pMsg);
public:
	CWispDIBList*	m_StateDIBList;
	CWispString		m_OrgAsmInstraction;
	int				m_ScrollSpace;
	CODE_VIEW_ADDR_MOD	m_AddrShowMode;
	ULPOS			m_BaseActiveAddress;
	ULPOS			m_CurAddr;
	ULPOS			m_LastAddr;
	COLORREF		m_ColorTable[MAX_COLOR];
	CSyserCodeDoc*	m_pCodeDoc;
	CWispDIBList	m_ColIconList;
	CAddrList		m_AddrList;
	CAddrList::IT	m_AddrIter;
	HANDLE			m_hPopupMenuItem;
	int				m_PopupMenuCol;
	ULPOS			m_RightMenuDataRefAddr;
	CWispMenu		m_PopupMenu;
	HANDLE			m_hRemoveItem;
	NEAR_JMP_ENRTY	m_NearJmpPos[MAX_JMP_LINE_COUNT];
	int				m_NearJmpCount;
	int				m_iActivedNearJmp;
	int				m_JmpLineSpace;
	void			DrawJmpLine(NEAR_JMP_ENRTY*pEntry,int Index,COLORREF Color);
	bool			GetItemLineByAddr(ULPOS Address,int *pLine);
	void			UpdateNearJmpState();
	ULSIZE			ColorDasm(ULPOS EIP,ULSIZE MaxSize,WISP_COLOR_CHAR*pColorString,ULSIZE nCodeAlgn = 0,INSTRUCTION_INFORMATION* DasmInstr=NULL,BYTE* CodeBuff=NULL);
private:
	WISP_COLOR_CHAR*InstrToCS(OUT const INSTRUCTION_INFORMATION*pDasmInstr,WISP_COLOR_CHAR*pColorString);//²ÊÉ«·´»ã±à
	WISP_COLOR_CHAR*OptItemToCS(const OPERAND_ITEM*OpArray,int nOp,WISP_COLOR_CHAR*pColorString,const INSTRUCTION_INFORMATION*pDasmInstr);
	WISP_CHAR		m_HighlightString[256];
	BYTE			m_HighlightTXTColor,m_HighlightBKColor;
	CODEHOTKEYMAP	m_HotKeyMap;
	void			AttachShortcutKey();

};


#endif
