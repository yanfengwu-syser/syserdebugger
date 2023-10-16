#ifndef _ANALYZER_H_
#define _ANALYZER_H_

#include "LogicStateCAD.h"

class CFunction
{
public:
	bool		m_bLibFunc;
	CStrW		m_Name;
	ULPOS		m_Start;
	ULPOS		m_End;
	ULPOS		m_CmtEnd;
	TMap<ULPOS,CFunction*> m_ChildFunc;
};

typedef TMap<ULPOS,CFunction*>		TChildFuncMap;
typedef TMap<ULPOS,CFunction>		TFuncMap;

#define	AS_NO_SYM						0x00000001

class CFuncCodeMaker
{
public:
	BYTE dbCheckSum;
	WORD dwCheckSum,dwVal,InstrCount;
	DWORD ddCheckSum,ddVal;
public:
	void MakeFirst(STFuncCode*pFuncCode);
	void MakeNext(BYTE*CodeBuffer,STFuncCode*pFuncCode);
	void MakeEnd(STFuncCode*pFuncCode,int Size);
	static void Make(BYTE*CodeBuffer,int Size,STFuncCode*pFuncCode);
};

class CAnalyzer
{
public:
	CAnalyzer();
	~CAnalyzer();
public:
	UINT		m_Style;
	CPageMemory	m_ImageCache;
	CImageFile*	m_pImageFile;
	CPEFile		m_PEFile;
	TFuncMap	m_FuncMap;
	int			m_AnalyzerDeep;
	CFuncCodeMaker		m_FuncCodeMaker;
	TArray<BYTE,MP_SIZE>m_CodeBuffer;
	CFuncDescrMap	m_FuncDescrMap;
	TList<DWORD>	m_RecogPathAddrList;
	TList<STPathMethod>	m_RecogPathMethodList;
	TList<STRecogCode>	m_RecogCodeList;
	STReportInfo	m_ReportInfo;
public:
	int		ReadMemory(ULPOS Address,void*Buffer,int Size);
	bool	IsInvalidAddress(ULPOS Address);
public://X86 PE
	bool	Open(PCSTR FileName);
	bool	Open(DWORD ModuleBase,DWORD ModuleSize=0,RWProc RMFunction=NULL,void*RMParam=NULL);
	void	Close();
	bool	LoadFDC(PCSTR FileName = NULL);
	bool	AnalyzerFromEntryPoint(int Deep,int MaxFuncCount);
	bool	AnalyzerFromExportFunction(int Deep,int MaxFuncCount);
	bool	Analyzer(ULPOS Address,int Deep,int MaxFuncCount);
	bool	AnalyzerFunction(CFunction*pFun,int Deep,int&CountLeft);
	static	int	GetFuncSize(BYTE*CodeBuff,int Size);
	void 	MakeFuncDescr(ULPOS Start,ULSIZE Size,STFuncCode*pFuncCode);
	PCWSTR	AnalyzerScan(CLogicStateCAD*pStateCAD);
	STStatePathEntry*AnalyzerScanPath(ULPOS BaseAddr,STStatePathEntry*pParentEntry);
	STStatePathEntry*PathFunc(ULPOS BaseAddr,STStatePathEntry*pParentEntry);
	STStatePathEntry*PathInitTermTable(ULPOS BaseAddr,ULSIZE Count,ULSIZE Length,STStatePathEntry*pParentEntry);
};

#endif

