#ifndef _SOURCECODEWND_H_
#define _SOURCECODEWND_H_

#include "SyserUI.h"
#include "SyserSymAnalyzer.h"

typedef TList<PSDUDTDATAITEM> CONTEXTDATALIST;
typedef TList<PSDFUNCTIONITEM> CONTEXTFUNCLIST;

class CCurrentFunction
{
	static int m_GeneralRegisterIndexMap[8];
public:
	CCurrentFunction();
	virtual ~CCurrentFunction();
	void Init(CSDSModule* pSDSModule,PSDFUNCTIONITEM pFuncItem=NULL);
	DWORD m_BeginAddress;
	DWORD m_EndAddress;
	DWORD m_Size;
	CSDSModule* m_pSDSModule;
	PSDFUNCTIONITEM m_pFunction; 
	void InitVariableList();
	char* FindNameByRegisterOffset(IN DWORD Offset,IN DWORD RegIndex=5,PSDUDTDATAITEM* pUdtData=NULL);
	CONTEXTDATALIST m_ContextDataList;
	CONTEXTFUNCLIST m_ContextFuncList;
	PSDTYPE_INFILE m_CurrentClass;
	void AddUdtDataMember(PSDTYPE_INFILE pType);
	void AddUdtFuncMember(PSDTYPE_INFILE pType);
	PSDUDTDATAITEM GetDataSymbolByName(char* Name,bool bCase=true);
	PSDFUNCTIONITEM GetFunctionSymbolByName(char* Name,bool bCase=true);
};

#define TXTFILE_OPEN_CONTAIN_NEWLINE		0x1		//在行的末尾
#define TXTFILE_OPEN_CONTAIN_LINEOFFSET		0x2		//在类的 m_LineOffsetLine 成员中保存每行在文件中的偏移

typedef TList<unsigned int>		TTETLineOffsetList;

class CSrcTXTFile : public CTXTFile
{
public:
	bool	Open(PCSTR FileName,HANDLE*pHandleOpen = NULL,UINT Style=0);
	TTETLineOffsetList m_LineOffsetLine;
	UINT	m_TxtStyle;
};


class CSourceCodeWnd:public CWispList
{
	enum
	{
		CPLUSPLUS_KEYWORD = MAX_COLOR,	//C++ 的关键字
		CPLUSPLUS_IDENTIFIER,			//C++的　id
		CPRE_KEYWORD,					//预处理器的关键字
		CPLUSPLUS_COMMENT_BLOCK,		//　注释块 也就是包含在 /*      */ 中间的注释
		CPLUSPLUS_COMMENT_LINE,			//单行的注释　也就是用 // 开始的注释
		CPLUSPLUS_STRING,
		CPLUSPLUS_NUMERICAL,
		CPLUSPLUS_OPERATION,
		CPLUSPLUS_CLASS_NAME,
		CPLUSPLUS_STRUCT_NAME,
		CPLUSPLUS_UNION_NAME,
		CPLUSPLUS_TYPEDEF_NAME,
		CPLUSPLUS_FUNCTION_NAME,
		CPLUSPLUS_UNKNOW,
		SYNTAXCOLOR_MAX,
	};
	COLORREF	m_Color[SYNTAXCOLOR_MAX];
	CSrcTXTFile m_TxtFile;
	bool m_FileOpen;
	int m_TxtFileLineNumber;
	LINENUMBERMAP m_LineMap;

public:
	CSourceCodeWnd(void);
	~CSourceCodeWnd(void);
public:
	void	ItemClickNotify(HANDLE hItem,int Col);
	void	ItemRClickNotify(HANDLE hItem,int Col);
	bool	ItemShowTipNotify(HANDLE hItem,int Col,int*pX,int*pY,WISP_PSTR szTip);
	bool	BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	bool	EndEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnUpdateClient)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventCollapse)
	DECLARE_WISP_MSG_EVENT(OnEventExpansion)
	DECLARE_WISP_MSG_EVENT(OnEventGoToLine)
	DECLARE_WISP_MSG_EVENT(OnEventAddWatch)
	DECLARE_WISP_MSG_EVENT(OnEventToggleBreakPoint)
	DECLARE_WISP_MSG_EVENT(OnEventToggleBreakPointState)
	DECLARE_WISP_MSG_EVENT(OnEventToggleBookMarks);
	DECLARE_WISP_MSG_EVENT(OnEventGotoHere)
	DECLARE_WISP_MSG_EVENT(OnEventSetEIP)
	WISP_COLOR_CHAR*ColorDasm(DWORD BaseAddress,DWORD EIP,DWORD MaxSize,WISP_COLOR_CHAR*pColorString,DWORD nCodeAlgn = 0);
	WISP_COLOR_CHAR*InstrToCS(OUT INSTRUCTION_INFORMATION*pDasmInstr,WISP_COLOR_CHAR*pColorString);//彩色反汇编
	WISP_COLOR_CHAR*OptItemToCS(OPERAND_ITEM*OpArray,int nOp,WISP_COLOR_CHAR*pColorString,INSTRUCTION_INFORMATION*pDasmInstr,DIS_CPU*pCurrent_CPU);
	CSDSModule*	GetSourceFileSymAnalyzer()const;
	ULONGLONG	GetBookMarkKey(HANDLE hItem);
	ULPOS	GetItemAddress(HANDLE hItem);
	bool	UpdateView();//如果包含EIP返回true
	void	LoadSourceFile(char* Buffer,DWORD size,PSDSOURCEFILEID pSDSourceFileId);
	int		GetSourceFileID()const;
	bool	GetVariable(const char* Name,HANDLE hItem,CStrA& OutBuffer);
	void	LoadModuleImage();
	void	SyntaxColor(char* SourceCodeLine,WISP_COLOR_CHAR* szColorBuffer);
	bool	GetStringValue(IN char* pString,IN int nLen,OUT CStrA& OutBuffer);
	bool	GetContextString();//右键彩单弹出时鼠标下的字符串 用在add watch 的参数
	void	SetBeginLine(DWORD Rva);
	void	PopupMenu(IN WISP_MSG*pMsg);
	//BookMark
	bool	IsBookMark(ULONG iLine);
	void	ToggleBookMark();
	void	GotoNextBookMark();
	void	GotoPrevBookMark();
	void	ClearAllBookMark();
	CCurrentFunction m_CurrentFunction;
	bool			m_CommentState;
	DIS_CPU			m_CurrentCpu;
	CSyserCodeDoc*	m_pCodeDoc;
	CWispDIBList*	m_StateDIBList;
	DWORD			m_CurrentFileID;
	CSDSModule*		m_pSDSModule;
	CWispMenu		m_PopupMenu;
	WISP_POINT		m_RightButtonPoint;
	TMap<ULONG,HANDLE> m_BookMark;
	ULPOS			m_CurModuleBase;
	CStrA m_ContextString;
	CStrA m_FullContextString;
};
#endif //_SOURCECODEWND_H_