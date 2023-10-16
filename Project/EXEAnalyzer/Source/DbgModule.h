#ifndef _DBG_MODULE_H_
#define _DBG_MODULE_H_

#define MAX_CMT_LEN				128

//////////////////////////////////////////////
//字符类型定义
typedef CHAR					SYMCHAR;
typedef CHAR					CMTCHAR;

typedef SYMCHAR*				PSYMSTR;
typedef const SYMCHAR*			PCSYMSTR;
typedef TString<SYMCHAR,true>	CSymStr;

typedef CMTCHAR*				PCMTSTR;
typedef const CMTCHAR*			PCCMTSTR;
typedef TString<CMTCHAR>		CCmtStr;

typedef TMap<ULPOS,CCmtStr>		CCommentMap;
typedef TMap<ULPOS,CSymStr>		CSymbolMap;
//字符类型定义
//////////////////////////////////////////////

#define MAKE_MODULE_ID(CheckSum,TimeDateStamp)				MAKE_QDWORD(CheckSum,TimeDateStamp)

typedef ULONGLONG		MODULE_ID;

class CSymbolModule
{
public:
	CSymbolModule();
public:
	virtual	bool	InsertSymbol(IN ULPOS Offset,IN PCSYMSTR szSym);
	virtual	bool	SetSymbol(IN ULPOS Offset,IN PCSYMSTR szSym);
	virtual	bool	RemoveSymbol(IN ULPOS Offset);
	virtual	bool	RemoveSymbol(IN PCSYMSTR szSym);
	virtual bool	GetAddress(IN PCSYMSTR szSym,OUT ULPOS*pAddress);
/////////////////////////////////////////////////////////////////////////
public:
	ULPOS			m_ModuleBase;
	ULSIZE			m_ModuleSize;
	CSymbolMap		m_SymbolMap;
	CSymStr			m_ModuleName;
	int				m_ReferenceCount;
	void*			m_pParam;
	MODULE_ID		m_ModuleID;
};

#define CMT_MODULE_VER				0x1000

class CCommentModule
{
public:
	CCommentModule();
	virtual	bool	InsertComment(IN ULPOS Offset,IN PCCMTSTR szComment);
	virtual	bool	SetComment(IN ULPOS Offset,IN PCCMTSTR szComment);
	virtual	bool	RemoveComment(IN ULPOS Offset);
	int	Save(ALTFileStream&Stream);
	int	Load(ALTFileStream&Stream);
	CCommentMap		m_CommentMap;
	CCmtStr			m_ModuleName;
	int				m_ReferenceCount;
	void*			m_pParam;
	MODULE_ID		m_ModuleID;
};

//以文件名为Key的符号容易，避免符号重复加载
class CSymbolContainer : public TMap<MODULE_ID,CSymbolModule>
{
public:
	virtual	CSymbolModule*GetSymbolModule(MODULE_ID MID);
	virtual	CSymbolModule*InsertSymbolModule(MODULE_ID MID);
	virtual	bool	RemoveSymbolModule(MODULE_ID MID);
	virtual	void	RemoveUnusedSymbolModule();
	//以下只对绑定了ModuleBase的模块有效
	virtual	bool	GetFullSymbol(IN ULPOS Address,OUT PSYMSTR SymbolName,int MaxLength);
	virtual	PCSYMSTR	GetSymbol(IN ULPOS Address);
};

class CCommentContainer : public TMap<MODULE_ID,CCommentModule>
{
public:
	virtual	CCommentModule*GetCommentModule(MODULE_ID MID);
	virtual	CCommentModule*InsertCommentModule(MODULE_ID MID);
	virtual	bool	RemoveCommentModule(MODULE_ID MID);
	virtual	void	RemoveUnusedCommentModule();
	int	Save(ALTFileStream&Stream);
	int	Load(ALTFileStream&Stream);
};

class CDbgModule
{
public:
	static	PCSYMSTR m_SplitStr;
	CDbgModule();
public:
	virtual	bool	GetOffset(IN PCSYMSTR szSym,OUT ULPOS*pOffset);
	virtual	bool	GetAddress(IN PCSYMSTR szSym,OUT ULPOS*pAddress);
	virtual	bool	GetFullSymbol(IN ULPOS Address,OUT PSYMSTR SymbolName,int MaxLength);
	virtual	PCSYMSTR	GetSymbol(IN ULPOS Address);
	virtual	PCCMTSTR	GetComment(IN ULPOS Address);
	virtual	bool	GetNearbySymbolAddrress(INOUT ULPOS*pAddress);
	virtual	void	AttachSymbolModule(CSymbolModule*pSymbolModule);
	virtual	void	DetachSymbolModule(CSymbolContainer*pSymContainer);
	virtual	void	AttachCommentModule(CCommentModule*pCommentModule);
	virtual	void	DetachCommentModule(CCommentContainer*pCmtContainer);
public:
	CSymbolModule*m_pSymbolModule;
	CCommentModule*m_pCommentModule;
	CSymStr		m_ModuleFullName;
	CSymStr		m_ModuleTitle;
	PCSYMSTR	m_ModuleName;
	ULPOS		m_ModuleBase;
	ULSIZE		m_ModuleSize;
	void*		m_pParam;
	MODULE_ID	m_ModuleID;
};

typedef TRangeMap<ULPOS,CDbgModule>	CDbgModuleMap;

class CDbgModuleList
{
public:
	virtual	CDbgModule*	GetModule(IN PCSYMSTR szModule);
	virtual	CDbgModule*	GetModule(IN ULPOS Address);
	virtual	CDbgModule*	GetModuleByID(IN MODULE_ID ModuleID);
	virtual	CDbgModule*	InsertModule(IN PCSYMSTR szModuleFullName,ULPOS Address,ULSIZE Size,MODULE_ID ModuleID);
	virtual	bool		RemoveModule(IN ULPOS Address);
	virtual	bool		GetFullSymbol(IN ULPOS Address,INOUT PSYMSTR szSym,int MaxLength);
	virtual	PCSYMSTR	GetSymbol(IN ULPOS Address);
	virtual	bool		GetNearbySymbolAddrress(INOUT ULPOS*pAddress);
	virtual	PCCMTSTR	GetComment(IN ULPOS Address);
public:
	CDbgModuleMap		m_DbgModuleMap;
};


#endif
