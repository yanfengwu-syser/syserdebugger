#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

enum BP_STATE
{
	BP_STATE_DISABLE=0,				//无效
	BP_STATE_ENABLE,				//有效
	BP_STATE_RECOV,					//要恢复的断点
	BP_STATE_RECOV_COPY_ON_WRITE,	//因物理地址改变要恢复的断点
	BP_REV_BPR_TYPE = 0x40000000,	//要恢复的 BPR 类型的断点，主要是设置页的 P 属性
	BP_SET_BPR_TYPE = 0x80000000    //已经设置了 BPR 类型的断点 
};

typedef struct _BP_RANGE_INFO
{
	DWORD	RangeStartAddress;
	DWORD	RangeLength;
	DWORD	State;	
	DWORD	Type; //1 read ,2 write, 4 execute  read and write	
	DWORD	PTEAddress;
	WORD   PTESize;
	WORD   PTECount;
	DWORD	PageSize;
	CStrA	Condition;					//条件用于断点时比较
	CStrA	DoCmd;						//触发时执行的命令
}BP_RANGE_INFO;


struct MODULE_BP
{
	CIStrA		ModuleFileName;
	CStrA		Condition;
	CStrA		Name;
	CStrA		DoCmd;						//触发时执行的命令
	BP_STATE	State;
};

typedef struct _BREAK_POINT
{
	CStrA		Name;						//名字用于显示
	CStrA		Description;				//描述,数据断点用来存放类型RW,W,X
	CStrA		Condition;					//条件用于断点时比较
	CStrA		OwnerName;					//进程名字用于显示
	CStrA		DoCmd;						//触发时执行的命令
	UINT		BPCount;					//断点被执行的次数，只要断点被执行到都会增加这个次数。不管他的条件是否为真
	ULPOS		Address;					//断点虚拟地址
	UINT		PID;						//进程ID
	BP_STATE	State;						//断点状态
	UINT		Type;						//断点类型
	UINT		Length;						//断点长度,用于数据断点
	NUM_PTR		UserData;					//自定义数据,Patch断点用来存放Patch函数指针
	MODULE_BP*	pModuleBP;
	BYTE		CodeBackup;
}BREAK_POINT,*PBREAK_POINT;

typedef TMap<ULONGLONG,BREAK_POINT>	CCodeBPMap;
typedef TMap<ULPOS,MODULE_BP>		CModuleBPMap;
typedef TList<BREAK_POINT>			CDataBPList;

#define BP_TYPE_HARDWARE			0x00000001
#define BP_TYPE_EXECUTE				0x00000002			//硬件执行断点
#define BP_TYPE_WRITE				0x00000004
#define BP_TYPE_READ				0x00000008
#define BP_TYPE_READWRITE			(BP_TYPE_WRITE|BP_TYPE_READ)
#define BP_TYPE_IO_WRITE			0x00000010
#define BP_TYPE_IO_READ				0x00000020
#define BP_TYPE_IO_READWRITE		(BP_TYPE_IO_READ|BP_TYPE_IO_WRITE)

#define BP_TYPE_PATCH				0x00000100
#define BP_TYPE_DEBUG				0x00000200
#define BP_TYPE_ONCE				0x00000400

#define BP_TYPE_FULL_CMP			0x80000000
#define BP_TYPE_INC_ALL				0x00000000
#define BP_TYPE_EXC_NON				0x00000000

enum
{
	DEBUG_PLUNGE_OTHER,
	DEBUG_PLUNGE_BREAK_POINT,
	DEBUG_PLUNGE_HARD_BREAK_POINT,
	DEBUG_PLUNGE_STEP,
	DEBUG_PLUNGE_EXCEPTION,
	DEBUG_PLUNGE_USER_BREAK,
};

enum TRACE_TYPE
{
	TRACE_NULL,
	TRACE_STEP_RANGE_IN,
	TRACE_STEP_RANGE_OUT,
	TRACE_PROCEED_STEP_RANGE_IN,
	TRACE_PROCEED_STEP_RANGE_OUT,
	TRACE_STEP_COUNT,
	TRACE_PROCEED_STEP_COUNT,
	TRACE_CONDITION,
	TRACE_PROCEED_CONDITION,
	TRACE_X86_RET_BREAK,
	TRACE_PAGE_RANGE_BREAK,
	TRACE_RECOVER_BREAK_POINT, //用来恢复 int3 软件断点
	TRACE_MAX_COUNT
};

class CDebugger;
class CCodeDoc;
class CSymbolContainer;
class CCommentContainer;

bool IsTypeMatched(UINT TypeInc,UINT TypeExc,BREAK_POINT&BP);

class CDebugInterface//界面提供给CDebugger的回调接口函数
{
	friend class CDebugger;
public:
	CCodeDoc*			m_pCodeDoc;
	CSymbolContainer*	m_pSymbolContainer;
	CCommentContainer*	m_pCommentContainer;
public:
	CDebugInterface();
	virtual void	OnLoadModule(CDebugger*pDbgProc,PCSTR szFileName,ULPOS ModuleBase,ULSIZE ModuleSize,MODULE_ID ModuleID)=0;
	virtual void	OnUnloadModule(CDebugger*pDbgProc,ULPOS ModuleBase)=0;
	//////////////////////////////////////////////////////////
	//调试相关
	//////////////////////////////////////////////////////////
	virtual void	UpdateTraceConditionVal(){};
	virtual bool	OnDebugTerminate(bool bCloseDoc)=0;
	virtual bool	OnDebugPlunge(UINT PlungeType)=0;
	virtual bool	OnDebugTerminateMultiThread(bool bCloseDoc)=0;	//调试器有单独线程
	virtual bool	OnDebugPlungeMultiThread(UINT PlungeType)=0;	//调试器有单独线程
	virtual void	DisplayMsg(PCSTR szMessage){}
	virtual void	UpdateContext(){}
	virtual	bool	TestCondition(PCSTR szCondition,PBREAK_POINT pBP=NULL){return true;}
	virtual bool	RunCmd(PCSTR szCmd){return false;}
	virtual void	RunCmdList(PCSTR szCmd){}
public://Trace
	virtual	bool	IsHandledTraceEvent();
	virtual void	SetTraceRange(ULPOS RangeStart,ULPOS RangeEnd,bool bRangeIn = false);
	virtual void	SetProceedRange(ULPOS RangeStart,ULPOS RangeEnd,bool bRangeIn = false);
	virtual	void	SetTraceCondition(PCSTR szTraceCondition);
	virtual	void	SetTraceProceedCondition(PCSTR szTraceCondition);
	virtual void	SetTracePageRangeCondition(DWORD dwPageCR2,DWORD dwPageEIP);
	virtual	void	SetTraceCount(int StepCount);
	virtual	void	SetProceedCount(int StepCount);
	virtual	void	SetX86RetBreak(CDebugger*pDbg);
	virtual	void	ResetTrace();
	virtual bool	CalcPageRangeCondition();
	virtual	CDebugger*GetCurrentDebugger()=0;
	CStrA			m_strTraceCondition;
	CDebugger*		m_TraceDebugger;
	int				m_TraceCount;
	TRACE_TYPE		m_TraceType;
	ULPOS			m_RangeStart;
	ULPOS			m_RangeEnd;
	ULPOS			m_PageCR2;//主要用于 BPR 内存范围断点使用。这个变量是缺页中断发生时的缺页地址
	ULPOS			m_PageEIP;//主要用于 BPR 内存范围断点使用。这个变量是缺页中断发生时的EIP值
};

enum
{
	BP_ERROR_SUCCESS = 0,
	BP_ERROR_SWITCH_PROCESS,
	BP_ERROR_MAP_TO_PHYS,
	BP_ERROR_BP_EXIST,
	BP_ERROR_BP_NOT_EXIST,
	BP_ERROR_FAIL_TO_SET,
	BP_ERROR_FAIL_TO_CLEAR,
};


class CDebugger
{
public:
	CDebugger();
	virtual ~CDebugger();
public:
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//控制
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool		Init(CDebugInterface*pDebugInterface);//初始化Debug对象
	virtual void		Release();//释放Debug对象
	virtual bool		Open(PCSTR ModuleName);
	virtual bool		Close();
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//内存操作
	virtual ULSIZE		WriteMemory(ULPOS Address,void*Buffer,ULSIZE Size);	//写内存
	virtual ULSIZE		ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size);	//读内存
	virtual ULSIZE		MoveMem(ULPOS DesAddr,ULPOS SrcAddr,ULSIZE Size);	//在进程空间内移动
	virtual ULSIZE		CmpMem(ULPOS DesAddr,ULPOS SrcAddr,ULSIZE Size);	//在空间内比较内存
	virtual ULPOS		SearchMem(ULPOS Address,ULSIZE Length,BYTE*ByteCode,ULSIZE Size,bool bCase = true);
	static	ULSIZE		ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size,void*Param);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//寄存器
	virtual bool		UpdateRegister();									//更新寄存器
	virtual bool		SaveRegister();										//改变寄存器
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//断点
	virtual bool		SetCodeBreakPoint(BREAK_POINT&BP);					//设置代码断点
	virtual bool		ClearCodeBreakPoint(BREAK_POINT&BP);				//清除代码断点
	virtual bool		SetDataBreakPoint(BREAK_POINT&BP);					//设置数据断点
	virtual bool		ClearDataBreakPoint(BREAK_POINT&BP);				//清除数据断点
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//进程
	virtual bool		MapToPhysAddr(ULPOS Address,ULONGLONG&PhysAddr);
	virtual	bool		SwitchProcessSpace(UINT PID);						//切换到指定进程空间
	virtual	void		RestoreProcessSpace();								//恢复进程空间
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//调试控制
	virtual bool		SetSingleStep();									//设置单步断点
	virtual bool		RemoveSingleStep();									//去除单步断点
	virtual bool		ContinueDebug(bool bRestoreScreen = true);			//继续程序
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Code BP 管理
	virtual	BREAK_POINT*GetCodeBP(ULPOS Address,UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	virtual	BREAK_POINT*InsertCodeBP(ULPOS Address,UINT Type,BP_STATE State = BP_STATE_ENABLE);
	virtual	bool		RemoveCodeBP(ULPOS Address,UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	virtual	bool		RemoveCodeBP(BREAK_POINT*pBP);
	virtual	int			RemoveAllCodeBP(UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	virtual	int			EnableAllCodeBP(UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	virtual	int			DisableAllCodeBP(UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	virtual	bool		EnableCodeBP(BREAK_POINT*pBP);
	virtual	bool		EnableCodeBP(ULPOS Address,UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	virtual	bool		DisableCodeBP(BREAK_POINT*pBP);
	virtual	bool		DisableCodeBP(ULPOS Address,UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Data BP 管理
	virtual	int			GetDataBPList(UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON,TList<BREAK_POINT*>*pList = NULL);
	virtual	BREAK_POINT*InsertDataBP(ULPOS Address,UINT Type,BP_STATE State,UINT Length);
	virtual	int			RemoveDataBP(ULPOS Address,UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	virtual	bool		RemoveDataBP(BREAK_POINT*pBP);
	virtual	int			RemoveAllDataBP(UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	virtual	int			EnableAllDataBP(UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	virtual	int			DisableAllDataBP(UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	virtual	bool		EnableDataBP(BREAK_POINT*pBP);
	virtual	int			EnableDataBP(ULPOS Address,UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	virtual	bool		DisableDataBP(BREAK_POINT*pBP);
	virtual	int			DisableDataBP(ULPOS Address,UINT TypeInc = BP_TYPE_INC_ALL,UINT TypeExc = BP_TYPE_EXC_NON);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	CCodeBPMap			m_CodeBPMap;
	CDataBPList			m_DataBPList;
public:
	UINT				m_PID;
	CStrA				m_ProcName;
	ULPOS*				m_pExecutePoint;
	CDebugInterface*	m_pDebugInterface;
	CDbgModuleList		m_ModuleList;
	CCodeBPMap*			m_pCodeBPMap;
	CDataBPList*		m_pDataBPList;
	UINT				m_LastError;
};

#endif
