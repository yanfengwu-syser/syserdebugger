#ifndef _LOGIC_STATE_CAD_H_
#define _LOGIC_STATE_CAD_H_

struct STReportInfo			//目标信息
{
	enum
	{
		RI_TYPE_COMMENT,
		RI_TYPE_REPORT
	};
	UINT		ID;
	UINT		Type;
	CStrW		Name;
	//序列化
	int	Save(ALTFileStream&Stream)
	{
		int Length;
		Length=Stream.Puts(&ID,sizeof(ID));
		Length+=Stream.Puts(&Type,sizeof(Type));
		Length+=Name.Save(Stream);
		return Length;
	}
	int	Load(ALTFileStream&Stream)
	{
		int Length;
		Length=Stream.Gets(&ID,sizeof(ID));
		Length+=Stream.Gets(&Type,sizeof(Type));
		Length+=Name.Load(Stream);
		return Length;
	}
};

struct STFuncCode			//函数描述
{
	WORD	FuncSize;		//函数大小
	WORD	InstrCount;		//指令条数
	DWORD	dbCheckSum;		//指令码BYTE校验和
	DWORD	dwCheckSum;		//指令码WORD校验和
	DWORD	ddCheckSum;		//指令码DWORD校验和
	bool operator<(const STFuncCode&FuncCode)const
	{
		if(ddCheckSum<FuncCode.ddCheckSum)
			return true;
		if(ddCheckSum>FuncCode.ddCheckSum)
			return false;
		if(dwCheckSum<FuncCode.dwCheckSum)
			return true;
		if(dwCheckSum>FuncCode.dwCheckSum)
			return false;
		if(dbCheckSum<FuncCode.dbCheckSum)
			return true;
		if(dbCheckSum>FuncCode.dbCheckSum)
			return false;
		if(InstrCount<FuncCode.InstrCount)
			return true;
		if(InstrCount>FuncCode.InstrCount)
			return false;
		if(FuncSize<FuncCode.FuncSize)
			return true;
		if(FuncSize>FuncCode.FuncSize)
			return false;
		return false;
	}
	bool operator==(const STFuncCode&FuncCode)const
	{
		return	FuncSize==FuncCode.FuncSize && InstrCount==FuncCode.InstrCount && 
				dbCheckSum==FuncCode.dbCheckSum && dwCheckSum==FuncCode.dwCheckSum && ddCheckSum==FuncCode.ddCheckSum;
	}
	bool operator!=(const STFuncCode&FuncCode)const
	{
		return !operator==(FuncCode);
	}
	int	Save(ALTFileStream&Stream)
	{
		return Stream.Puts(this,sizeof(STFuncCode));
	}
	int	Load(ALTFileStream&Stream)
	{
		return Stream.Gets(this,sizeof(STFuncCode));
	}
};

struct STRecogCode
{
	enum RECOG_CODE_TYPE
	{
		FUNCTION,
		IGNORE_ENTRY
	};
	RECOG_CODE_TYPE CodeType;
	union
	{
		STFuncCode FuncCode;
	};
	bool operator<(const STRecogCode&RecogCode)const
	{
		switch(CodeType)
		{
		case FUNCTION:
			return FuncCode < RecogCode.FuncCode;
		default:
			CODE_WARNING("Error : 非法的识别类型");
			return false;
		}
	}
	bool operator!=(const STRecogCode&RecogCode)const
	{
		if(CodeType!=RecogCode.CodeType)
			return true;
		switch(CodeType)
		{
		case FUNCTION:
			return FuncCode < RecogCode.FuncCode;
		default:
			return false;
		}
	}
};

typedef TSet<STRecogCode>		CRecogCodeSet;

struct STPathMethod
{
	enum METHOD_TYPE
	{
		OFFSET,
		//Offset 目标相对于基址的偏移
		//Length 目标长度
		//Delta  修正偏移（用于Call）
		ADDR_PTR,
		//Offset 目标相对于基址的偏移
		//Length 目标长度
		//Delta  相对目标地址的偏移（用于VFTable）
		OFFSET_PTR,
		//Offset 目标相对于基址的偏移
		CPP_INIT_TERM_TABLE
		//Offset 构造函数表起始地址的偏移
		//Delta  构造函数表结束地址相对起始地址的偏移
	};
	METHOD_TYPE	Method;
	int	Offset;
	int	Length;
	int	Delta;
};

struct STStatePathEntry
{
	STRecogCode		RecogCode;
	STReportInfo	ReportInfo;
	STPathMethod	PathMethod;
	TSet<STStatePathEntry>	NextEntry;
	inline bool operator<(const STStatePathEntry&Entry)const{return RecogCode < Entry.RecogCode;}
	int	Save(ALTFileStream&Stream)
	{
		int Length = 0;
		Length=Stream.Puts(&RecogCode,sizeof(RecogCode));
		Length+=Stream.Puts(&PathMethod,sizeof(PathMethod));
		Length+=ReportInfo.Save(Stream);
		Length+=NextEntry.Save(Stream);
		return Length;
	}
	int	Load(ALTFileStream&Stream)
	{
		int Length = 0;
		Length=Stream.Gets(&RecogCode,sizeof(RecogCode));
		Length+=Stream.Gets(&PathMethod,sizeof(PathMethod));
		Length+=ReportInfo.Load(Stream);
		Length+=NextEntry.Load(Stream);
		return Length;
	}
};

typedef TSet<STStatePathEntry>	TStatePathEntrySet;

struct STFuncDescr
{
	CStrA	Name;
	CStrA	FullName;
	int	Save(ALTFileStream&Stream)
	{
		int Length;
		Length=Name.Save(Stream);
		Length+=FullName.Save(Stream);
		return Length;
	}
	int	Load(ALTFileStream&Stream)
	{
		int Length;
		Length=Name.Load(Stream);
		Length+=FullName.Load(Stream);
		return Length;
	}
};

typedef TMap<STFuncCode,STFuncDescr> CFuncDescrMap;

class CLogicStateCAD
{
public:
	CLogicStateCAD();
	~CLogicStateCAD();
public:
	bool	LoadRecord(PCSTR FileName);
	bool	InsertRecord(const STReportInfo&ReportInfo,const TList<STRecogCode>&RecogCodeList,const TList<STPathMethod>&PathMethodList);
	void	ClearRecord();
	STStatePathEntry	m_StateRoot;
	CALTFileStream		m_FileStream;
};

#endif
