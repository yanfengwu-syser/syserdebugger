#ifndef _SYSER_UI_H_
#define _SYSER_UI_H_

#include "Analyzer.h"
#include "CallStack.h"
#include "SyserSymAnalyzer.h"

class CSyserDI : public CDebugInterface
{
public://CDebugInterface接口
	void	OnLoadModule(CDebugger*pDbgProc,PCSTR szFileName,ULPOS ModuleBase,ULSIZE ModuleSize,MODULE_ID ModuleID);
	void	OnUnloadModule(CDebugger*pDbgProc,ULPOS ImageBase);
	bool	OnDebugTerminate(bool bCloseDoc);			//0环用
	bool	OnDebugPlunge(UINT PlungeType=0);			//0环用
	bool	OnDebugTerminateMultiThread(bool bCloseDoc);//3环用
	bool	OnDebugPlungeMultiThread(UINT PlungeType=0);//3环用
	void	UpdateTraceConditionVal();
	void	UpdateContext();
	void	DisplayMsg(PCSTR szMessage);
	bool	TestCondition(PCSTR szCondition,PBREAK_POINT pBP=NULL);
	bool	RunCmd(PCSTR szCmd);
	void	RunCmdList(PCSTR szCmd);
	CDebugger*GetCurrentDebugger();
	bool CalcPageRangeCondition();
	int CalcPageRangeCondition1();
};

class CSyserCodeDoc : public CCodeDoc ,public CInstrSym ,public CExpCalc
{
public:
	CSyserCodeDoc();
	virtual ~CSyserCodeDoc();
public:
	//CInstrSym接口
	bool	AddrToSym(ULPOS Address,PSTR szSym,int MaxLength);
	bool	GetInstrRefPoint(ULPOS*pAddress);
	ULSIZE	ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size);
public:
	//CCalcExp接口
	ULONG	GetPtrValue(ULONG Address);
	bool	GetValue(PCSTR szItem,ULONG*pValue);
	bool	GetValue(PCWSTR szItem,ULONG*pValue);
public:
	//CCodeDoc
	bool	Open(PCSTR Name);
	void	Close();
	ULSIZE	ReadImage(ULPOS Address,void*Buffer,ULSIZE Size);
	ULPOS	GetNextAddress(ULPOS Address,int Count);
	bool	GetSymbol(ULPOS Address,WCHAR*szSymbol,int BufSize);
	bool	GetComment(ULPOS Address,WCHAR*szComment,int BufSize);
	bool	SetSymbol(ULPOS Address,WCHAR*szSymbol);
	bool	SetComment(ULPOS Address,WCHAR*szComment);
	UINT	GetLineMark(ULPOS Address);
	bool	IsExecutePointVisible(ULPOS Address,ULSIZE Size);
public:
	X86_CPU_REG_PTR m_X86RegPtr;
	DWORD	m_EIPOpcode;
	DWORD	m_PopPID;		//进入断点时的进程 ID
	DWORD	m_PopTID;		//进入断点时的线称 ID
	DWORD	m_BPCount;		//当前断点的执行次数这个是动态变化的。和每个断点的结构相关联。
							//当一个断点触发时，动态改变这个变量的位置。在这里这个变量只是一个占位符。
	CStrA	m_MainModuleName;
	void	UpdateEIPOpcode();
	void	GetCurInstrInfo(WCHAR*szInfo);
	void	GetCurInstrInfoEx(WISP_COLOR_CHAR*szInfo,int ccLen);//用在 code view 窗口当前 EIP 处的 Comment 的现实使用
	void	UpdatePID_TID(DWORD PID,DWORD TID);
private:
	void	InsertX86RegSym(X86_CPU_REG_PTR*pRegPtr);
	void	HandleAddressOpForCodeView(ULPOS Address,WISP_COLOR_CHAR* szInfo,int ccLen);
};

struct BP_LOAD
{
	BP_STATE	State;
	UINT		Type;
};

typedef TMap<CIStrA,BP_LOAD>	CModuleLoadBPMap;
typedef TList<BP_RANGE_INFO> BP_RANGE_LIST;
typedef TMap<DWORD,BP_RANGE_LIST> PROC_RANGE_BP_MAP;

class CSyserUI : public CSyserPluginUI
{
public:
	CSyserUI();
	~CSyserUI();
public:
	/////////////////////////////////////////////////////
	//Plugin
	bool		RegisterPluginModule(PCWSTR ModuleName,SYSER_PLUGIN_MODULE*pPluginModule);
	bool		UnregisterPluginModule(PCWSTR ModuleName);
	//Plugin
	/////////////////////////////////////////////////////
public:
	/////////////////////////////////////////////////////
	//Process
	void		AttackProcess(PCWSTR szProcName);
	//Process
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	//Command
	bool		InsertCmd(PCWSTR szCmd,FPCmd pCmdProc,void*pUserData,PCWSTR pComment,PCWSTR pUsage);
	void		RemoveCmd(PCWSTR szCmd);
	int			RunCmd(PCWSTR szCmd);
	void		Outputf(PCWSTR szMsg,...);
	void		Output(PCDSTR szMsg);
	//Command
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	//GUI
	HANDLE		InsertMenu(HANDLE hParentMenu,const WCHAR*szMenuName,FPMenuProc fpMenuProc);
	bool		RemoveMenu(HANDLE hMenu);
	bool		EnableMenu(HANDLE hMenu,bool bEnable);
	void*		GetMainTabWnd();
	void*		GetMainMenu();
	void*		GetWisp();
	//GUI
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	//Symbol
	bool		CalcExp(const WCHAR*szExp,ULONG*pResult);
	bool		CalcExp(const CHAR*szExp,ULONG*pResult);
	bool		SegmentFilter(const WCHAR*szExp,DWORD*pResult);
	bool		GetSegmentBaseAddress(const WCHAR* pStr,OUT WCHAR* pOutStr,OUT DWORD* SegmentBaseAddres,OUT DWORD* SegmentLimit);
	bool		GetSym(ULPOS Address,PSTR szSym,int MaxLength = MAX_SYMBOL_LEN);
	bool		GetAlmostSym(ULPOS Address,PSTR szSym);
	bool		IsASCIIString(ULPOS Address,PSTR szBuffer,int ccLen);
	bool		IsUNICODEString(ULPOS Address,WCHAR* szBuffer,int ccLen);
	bool		GetString(ULPOS Address, WCHAR* szBuffer,int ccLen,int& type);
	int			GetFullSymbol(PSTR szPart);
	//Symbol
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	//Comments
	bool		LoadComment();
	bool		SaveComment();
	//Comments
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	//Instruction
	int			GetInstrLen(DWORD Address);
	void		SetInstrMode(UINT Mode);
	//Instruction
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	//Process operation
	DWORD	WriteMemory(DWORD Address,void*Buffer,DWORD Size);
	DWORD	ReadMemory(DWORD Address,void*Buffer,DWORD Size);
	//Process operation
	/////////////////////////////////////////////////////

	CSDSModule* GetSDSModule(ULPOS EIP);
	bool		IsSDSModuleInProcess(CSDSModule*pSDSModule);//判断指定SDSModule是否存在于当前线程

	bool		ToggleCodeBP(ULPOS Address);
	bool		ToggleCodeBPState(ULPOS Address);

	bool		InsertCodeBP(ULPOS Address,PCSTR Name = NULL,PCSTR Contidion = NULL,PCSTR DoCmd = NULL);
	bool		RemoveCodeBP(ULPOS Address);

	void		EnableAllModuleBP(bool bEnable = true);
	bool		EnableModuleBP(ULPOS Address,bool bEnable = true);

	bool		InsertLoadBP(PCSTR ModuleName,UINT Type,BP_STATE State);
	bool		RemoveLoadBP(PCSTR ModuleName);
	void		EnableAllLoadBP(bool bEnable = true);
public:
	void		LoadAPIDefine();
	bool		IsPublicBP(ULPOS Address,PSTR ModuleName=NULL);
	void		SetPublicSymbolModuleBase();
	CAPIMap				m_APIMap;
	CSyserCodeDoc		m_CodeDoc;
	CSymbolContainer	m_SymbolContainer;
	CCommentContainer	m_CommentContainer;
	CSyserDI			m_SyserDI;
	CSDSModuleMap		m_SDSModuleMap;
	CCallStack			m_CallStack;
	CCodeBPMap			m_CodeBPMap;
	CDataBPList			m_DataBPList;
	CModuleBPMap		m_ModuleBPMap;
	CModuleLoadBPMap	m_ModuleLoadBPMap;
	int			AttachSymbolModuleToProcess(CSymbolModule*pSymMod);
	int			DetachSymbolModuleToProcess(CSymbolModule*pSymMod);
	int			AttachCommentModuleToProcess(CCommentModule*pCmtMod);
	int			DetachCommentModuleToProcess(CCommentModule*pCmtMod);
	CSymbolModule*LoadPESym(PCSTR szFileName,CDbgModule*pDbgMod=NULL);
	CSymbolModule*LoadIDAMapFile(PCSTR szIDAMapFile,PCSTR szFileName,CDbgModule*pDbgMod=NULL);
	bool		LoadTranslateSDS(PCSTR szFileName,ULPOS ModuleBase,ULSIZE ModuleSize);
	CSDSModule*	LoadSDSModule(PCSTR szSymbolModuleFile);
	bool		UnloadSDSModule(CSDSModule*pSDSModule);
	int			LoadSDSSymbol(CSDSModule*pSDSModule);	//装载SDS里的符号到符号模块
	bool		QuerySDS(PSYSER_QUER_SDS pSyserSDS);
};

extern PCSTR szPublicModuleName[];

ULSIZE			ReadDbgProcMemory(ULPOS Address,void*Buffer,ULSIZE Size,void*Param);

#endif
