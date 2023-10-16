#ifndef _ALT_EXP_CALC_HPP_
#define _ALT_EXP_CALC_HPP_

ALT_NAME_SPACE_BEGIN

#define FP_VALUE_FUNC_TYPE_DEF	typedef VALUE_TYPE (*FPValueFunc)(CHAR_TYPE*pszSym,void*Param)
#define EXP_CALC_MAX_LEVEL		6
#define EXP_MAX_OPT_STRLEN		2

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
class TExpCalcSym
{
public:
	enum TYPE
	{
		CONSTANT,
		PTR,
		FUNC,
	};
	FP_VALUE_FUNC_TYPE_DEF;
public:
	union
	{
		VALUE_TYPE	Const;
		struct
		{
			void*	Ptr;
			int		Length;
		}Ptr;
		struct
		{
			FPValueFunc fpValueFunc;
			void*		Param;
		}Func;
	}Value;
	TYPE Type;
};

struct STOptFunc
{
	CStrA	OptStr;
	int		Level;
	void*	OptFunc;
	void*	Param;
};

template<class CHAR_TYPE,class VALUE_TYPE>
class TExpItem
{
public:
	enum TYPE
	{
		RESULT,
		SYM,
		STR,
		OPTR
	};
	union
	{
		VALUE_TYPE	Value;
		STOptFunc*	pOptFunc;
		const CHAR_TYPE*pStr;
	}Value;
	TYPE Type;
	int	Length;
	const CHAR_TYPE*ItemStr;
};

template<class CHAR_TYPE,class VALUE_TYPE = int,bool bIgnoreCase = true>
class TExpCalc
{
public:
	typedef TList<STOptFunc>				STOptFuncList;
	typedef TExpItem<CHAR_TYPE,VALUE_TYPE>	STExpItem;
	typedef TList<STExpItem>				STExpItemList;
	typedef TListIter<STExpItem>			STExpItemListIT;
	typedef TString<CHAR_TYPE,bIgnoreCase>	CExpCalcStr;
	typedef TExpCalcSym<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>	CExpCalcSym;
	typedef TMap<CExpCalcStr,CExpCalcSym>		CExpCalcSymMap;
	typedef TMapIter<CExpCalcStr,CExpCalcSym>	CExpCalcSymMapIT;
	typedef STExpItem*(*PFOptFunc)(STExpItemListIT&OptIter,STExpItemList&ExpItemList,void*Param);
	FP_VALUE_FUNC_TYPE_DEF;
public:
	TExpCalc();
	bool	CalcExp(const CHAR_TYPE*ExpStr,VALUE_TYPE*pResult);
	bool	CalcExpA(const CHAR*ExpStr,VALUE_TYPE*pResult);
	bool	CalcExpW(const WCHAR*ExpStr,VALUE_TYPE*pResult);
	virtual bool GetValue (const CHAR_TYPE*szItem,VALUE_TYPE*pValue);
	virtual VALUE_TYPE GetPtrValue(VALUE_TYPE Address){return 0;}
	virtual int GetStringA(VALUE_TYPE Address,PSTR szBuffer,int MaxLen);
	virtual int GetStringW(VALUE_TYPE Address,PWSTR szBuffer,int MaxLen);
	virtual void GetMem(VALUE_TYPE Address,BYTE* Buffer,int Len);

	bool	InsertOptFunc(const char*szOpt,int Level,PFOptFunc pfOptFunc,void*Param);
	bool	InsertConstSym(CHAR_TYPE*szSym,VALUE_TYPE Value);
	bool	InsertPtrSym(CHAR_TYPE*szSym,void*pValue,int Length);
	bool	InsertFuncSym(CHAR_TYPE*szSym,FPValueFunc fpFunc,void*Param);
	void	ClearAllSym();
	void	ClearConstSym();
	void	ClearPtrSym();
	void	ClearFuncSym();
	bool	RemoveSym(CHAR_TYPE*szSym);
	bool	CheckCalcItem(int nPrev,STExpItemListIT&OptIter,int nNext,STExpItemList&ExpItemList);
	bool	RemoveCalcItem(const STExpItemListIT&BeginIter,int Count,STExpItemList&ExpItemList);
	bool	SetPtrValue(const CHAR_TYPE*szValue,VALUE_TYPE Value);
	STOptFuncList	m_OptFuncList;
	CExpCalcSymMap	m_SymMap;
private:
	bool CalcItem(STExpItemListIT&ItemIter,STExpItemList&ExpItemList);
	bool GetItemValue(STExpItem*pItem);
	bool GetItem(const CHAR_TYPE*ExpStr,STExpItemList&ExpItemList);
	STOptFunc*IsOptString(const CHAR_TYPE*ExpStr);
	//////////////////////////////////////////////////////////////////////////////////////////
	//Í¨ÓÃ²Ù×÷·û
	//////////////////////////////////////////////////////////////////////////////////////////
	static STExpItem*Null(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*PtrValue(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*LogicAnd(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*LogicOr(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*LogicXor(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*NotBelow(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*NotAbove(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*Below(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*Above(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*Equal(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*NotEqual(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*ShiftRight(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*ShiftLeft(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*Add(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*Sub(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*Mul(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*Div(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*Mod(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*Xor(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*Not(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*And(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*Or(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*LeftBracket(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
	static STExpItem*NonOptr(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis);
};

typedef TExpCalc<char>	CExpCalcA;
typedef TExpCalc<WCHAR>	CExpCalcW;

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::TExpCalc()
{
	InsertOptFunc("&&",5,(PFOptFunc)LogicAnd,this);
	InsertOptFunc("||",5,(PFOptFunc)LogicOr,this);
	InsertOptFunc("^^",5,(PFOptFunc)LogicXor,this);
	InsertOptFunc(">=",4,(PFOptFunc)NotBelow,this);
	InsertOptFunc("<=",4,(PFOptFunc)NotAbove,this);
	InsertOptFunc("==",4,(PFOptFunc)Equal,this);
	InsertOptFunc("!=",4,(PFOptFunc)NotEqual,this);
	InsertOptFunc(">>",1,(PFOptFunc)ShiftRight,this);
	InsertOptFunc("<<",1,(PFOptFunc)ShiftLeft,this);
	InsertOptFunc(">",4,(PFOptFunc)Above,this);
	InsertOptFunc("<",4,(PFOptFunc)Below,this);
	InsertOptFunc("+",3,(PFOptFunc)Add,this);
	InsertOptFunc("-",3,(PFOptFunc)Sub,this);
	InsertOptFunc("*",2,(PFOptFunc)Mul,this);
	InsertOptFunc("/",2,(PFOptFunc)Div,this);
	InsertOptFunc("%",2,(PFOptFunc)Mod,this);
	InsertOptFunc("@",1,(PFOptFunc)PtrValue,this);
	InsertOptFunc("^",1,(PFOptFunc)Xor,this);
	InsertOptFunc("!",1,(PFOptFunc)Not,this);
	InsertOptFunc("&",1,(PFOptFunc)And,this);
	InsertOptFunc("|",1,(PFOptFunc)Or,this);
	InsertOptFunc("(",0,(PFOptFunc)LeftBracket,this);
	InsertOptFunc(")",0,(PFOptFunc)NonOptr,this);
	InsertOptFunc("\"",0,(PFOptFunc)Null,this);
	InsertOptFunc("\'",0,(PFOptFunc)Null,this);
}


template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::CalcExp(const CHAR_TYPE*ExpStr,VALUE_TYPE*pResult)
{
	STExpItemList ExpItemList;
	if(ExpStr==NULL || *ExpStr==0)
	{
		*pResult = 0;
		return true;
	}
	if(GetItem(ExpStr,ExpItemList)==false)
		return false;
	if(CalcItem(ExpItemList.Begin(),ExpItemList)==false)
		return false;
	if(pResult)
		*pResult=ExpItemList.Begin()->Value.Value;
	return true;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::CalcExpA(const CHAR*ExpStr,VALUE_TYPE*pResult)
{
	CHAR_TYPE szBuffer[512];
	if(ExpStr==NULL)
		return false;
	TStrCpy(szBuffer,ExpStr);
	return CalcExp(szBuffer,pResult);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::CalcExpW(const WCHAR*ExpStr,VALUE_TYPE*pResult)
{
	CHAR_TYPE szBuffer[512];
	if(ExpStr==NULL)
		return false;
	TStrCpy(szBuffer,ExpStr);
	return CalcExp(szBuffer,pResult);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::InsertOptFunc(const char*szOpt,int Level,PFOptFunc pfOptFunc,void*Param)
{
	STOptFuncList::IT Iter;
	int OptLen = TStrLen(szOpt);
	for( Iter = m_OptFuncList.Begin();Iter!=m_OptFuncList.End();Iter++)
	{
		if(Iter->Level>Level || (Iter->Level==Level && OptLen>=Iter->OptStr.Length()) )
			break;
	}
	Iter = m_OptFuncList.InsertBefore(Iter);
	Iter->OptStr = szOpt;
	Iter->Level = Level;
	Iter->OptFunc = pfOptFunc;
	Iter->Param = Param;
	return true;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::InsertConstSym(CHAR_TYPE*szSym,VALUE_TYPE Value)
{
	CExpCalcSymMapIT Iter = m_SymMap.InsertUnique(szSym);
	if(Iter==m_SymMap.End())
		return false;
	Iter->Value.Const = Value;
	Iter->Type = CExpCalcSym::CONSTANT;
	return true;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::InsertPtrSym(CHAR_TYPE*szSym,void*pValue,int Length)
{
	CExpCalcSymMapIT Iter = m_SymMap.InsertUnique(szSym);
	if(Iter==m_SymMap.End())
		return false;
	Iter->Value.Ptr.Ptr = pValue;
	Iter->Value.Ptr.Length = Length;
	Iter->Type = CExpCalcSym::PTR;
	return true;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::InsertFuncSym(CHAR_TYPE*szSym,FPValueFunc fpFunc,void*Param)
{
	CExpCalcSymMapIT Iter;
	Iter = m_SymMap.InsertUnique(szSym);
	if(Iter==m_SymMap.End())
		return false;
	Iter->Value.Func.fpValueFunc = fpFunc;
	Iter->Value.Func.Param = Param;
	Iter->Type = CExpCalcSym::FUNC;
	return true;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
void TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::ClearAllSym()
{
	m_SymMap.Clear();
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
void TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::ClearConstSym()
{
	CExpCalcSymMapIT RemoveIter,Iter=m_SymMap.Begin();
	while(Iter!=m_SymMap.End())
	{
		if(Iter->Type == CExpCalcSym::CONST)
		{
			RemoveIter = Iter;
			Iter++;
			m_SymMap.Remove(RemoveIter);
		}
		else
		{
			Iter++;
		}
	}
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
void TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::ClearPtrSym()
{
	CExpCalcSymMapIT RemoveIter,Iter=m_SymMap.Begin();
	while(Iter!=m_SymMap.End())
	{
		if(Iter->Type == CExpCalcSym::PTR)
		{
			RemoveIter = Iter;
			Iter++;
			m_SymMap.Remove(RemoveIter);
		}
		else
		{
			Iter++;
		}
	}
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
void TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::ClearFuncSym()
{
	CExpCalcSymMapIT RemoveIter,Iter=m_SymMap.Begin();
	while(Iter!=m_SymMap.End())
	{
		if(Iter->Type == CExpCalcSym::FUNC)
		{
			RemoveIter = Iter;
			Iter++;
			m_SymMap.Remove(RemoveIter);
		}
		else
		{
			Iter++;
		}
	}
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::RemoveSym(CHAR_TYPE*szSym)
{
	CExpCalcSymMapIT Iter = m_SymMap.Find(szSym);
	if(Iter==m_SymMap.End())
		return false;
	m_SymMap.Remove(Iter);
	return true;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
STOptFunc*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::IsOptString(const CHAR_TYPE*ExpStr)
{
	static CHAR_TYPE OptrStr[]=
	{
		'`','~','!','@','#','$','%','^','&','*','(',')','-','+','=',
		'|','{','}',':',';','\"','\'','<','>',',','.','?','/','\\','\'','\"','\0'
	};
	if(TStrChr(OptrStr,*ExpStr)==NULL)
		return NULL;
	for(int OptLen = EXP_MAX_OPT_STRLEN; OptLen>0 ; OptLen--)
	{
		for(STOptFuncList::IT FuncIter=m_OptFuncList.Begin();FuncIter!=m_OptFuncList.End();FuncIter++)
		{
			if(OptLen== FuncIter->OptStr.Length() && TStrNCmp(ExpStr,(const char*)FuncIter->OptStr,FuncIter->OptStr.Length())==0)
				return &(*FuncIter);
		}
	}
	return NULL;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::GetItemValue(STExpItem*pItem)
{
	CHAR_TYPE NumStr[128];
	TStrCpyLimit(NumStr,pItem->ItemStr,pItem->Length+1);
	if(GetValue(NumStr,&pItem->Value.Value)==false)
	{
		pItem->Type = STExpItem::SYM;
		return false;
	}
	pItem->Type = STExpItem::RESULT;
	return true;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::GetItem(const CHAR_TYPE*ExpStr,STExpItemList&ExpItemList)
{
	static CHAR_TYPE IgnoreStr[]={'\r','\n','\t',' ','\0'};
	STOptFunc*pOptFunc;
	STExpItem*pExpItem,*PrevItem;
	int Begin,End,Length;
	Length=TStrLen(ExpStr);
	Begin = End = 0;
	PrevItem = NULL;
	while(End<Length)
	{
		if(TStrChr(IgnoreStr,ExpStr[End]))
		{
			if(PrevItem)
			{
				PrevItem->Length = End - Begin;								
				GetItemValue(PrevItem);
				PrevItem = NULL;
			}
		}
		else
		{
			pOptFunc = IsOptString(&ExpStr[End]);
			if(pOptFunc)
			{
				if(PrevItem)
				{
					PrevItem->Length = End - Begin;
					GetItemValue(PrevItem);
					PrevItem = NULL;
				}
				if(ExpStr[End]=='\"' || ExpStr[End]=='\'')
				{										
					pExpItem = &(*ExpItemList.Append());
					End++;
					Begin = End;
					pExpItem->ItemStr=&ExpStr[Begin];
					while(ExpStr[End] && ExpStr[End]!='\"' && ExpStr[End]!='\'')
						End++;
					pExpItem->Length=End-Begin;
					pExpItem->Value.pStr=&ExpStr[Begin];
					pExpItem->Type = STExpItem::STR;
					Begin = End;					
				}
				else
				{
					pExpItem = &(*ExpItemList.Append());
					pExpItem->ItemStr=&ExpStr[End];
					pExpItem->Length=pOptFunc->OptStr.Length();
					pExpItem->Value.pOptFunc=pOptFunc;
					pExpItem->Type = STExpItem::OPTR;
					End = Begin = End + pExpItem->Length - 1;
				}
			}
			else if(PrevItem==NULL)
			{
				PrevItem = &(*ExpItemList.Append());
				PrevItem->ItemStr = &ExpStr[End];
				PrevItem->Value.pOptFunc = NULL;
				Begin = End;
			}
		}
		End++;
	}
	if(PrevItem)
	{
		PrevItem->Length = End - Begin;
		GetItemValue(PrevItem);
		PrevItem = NULL;
	}
	return true;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::CheckCalcItem(int nPrev,STExpItemListIT&OptIter,int nNext,STExpItemList&ExpItemList)
{
	int n;
	STExpItemListIT Iter;
	Iter = OptIter-1;
	for(n=0;n<nPrev;n++)
	{
		if(Iter == ExpItemList.End())
			return false;
		if(Iter->Type != STExpItem::RESULT)
			return false;
		Iter--;
	}
	Iter = OptIter+1;
	for(n=0;n<nPrev;n++)
	{
		if(Iter == ExpItemList.End())
			return false;
		if(Iter->Type != STExpItem::RESULT)
			return false;
		Iter++;
	}
	return true;	
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::RemoveCalcItem(const STExpItemListIT&BeginIter,int Count,STExpItemList&ExpItemList)
{
	STExpItemListIT Iter = BeginIter;
	for(int n=0;n<Count;n++)
	{
		if(Iter==ExpItemList.End())
			return false;
		Iter++;
	}
	ExpItemList.Remove(BeginIter,Iter);
	return true;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::CalcItem(STExpItemListIT&ItemIter,STExpItemList&ExpItemList)
{
	STExpItem*pResult;
	STOptFunc*pOptFunc;
	STExpItemListIT CurItemIter = ItemIter;
	for(int Level=0;Level<EXP_CALC_MAX_LEVEL;Level++)
	{
		CurItemIter=ItemIter;
		while(CurItemIter!=ExpItemList.End())
		{
			if(CurItemIter->Type == STExpItem::OPTR)
			{
				pOptFunc=CurItemIter->Value.pOptFunc;
				if(pOptFunc->Level==Level)
				{
					pResult = ((PFOptFunc)pOptFunc->OptFunc)(CurItemIter,ExpItemList,this);
					if(pResult==NULL)
						return false;
					pResult->Type = STExpItem::RESULT;
					CurItemIter = *pResult;
				}
			}
			CurItemIter++;
		}
	}
	return ExpItemList.Count()==1 && ExpItemList.Begin()->Type == STExpItem::RESULT;
}


template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::SetPtrValue(const CHAR_TYPE*szValue,VALUE_TYPE Value)
{
	CExpCalcSymMapIT Iter = m_SymMap.Find(szValue);
	if(Iter==m_SymMap.End())
		return false;
	if(Iter->Type != CExpCalcSym::PTR)
		return false;
	memcpy(Iter->Value.Ptr.Ptr,&Value,Iter->Value.Ptr.Length);
	return true;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
bool TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::GetValue(const CHAR_TYPE*szItem,VALUE_TYPE*pValue)
{
	if(USHexStrToNum(szItem,pValue))
		return true;
	CExpCalcSymMapIT Iter = m_SymMap.Find(szItem);
	if(Iter!=m_SymMap.End())
	{
		switch(Iter->Type)
		{
		case CExpCalcSym::CONSTANT:
			*pValue = Iter->Value.Const;
			break;
		case CExpCalcSym::PTR:
			*pValue=0;
			TMemCpy((BYTE*)pValue,(BYTE*)Iter->Value.Ptr.Ptr,Iter->Value.Ptr.Length);
			break;
		case CExpCalcSym::FUNC:
			*pValue = Iter->Value.Func.fpValueFunc(Iter.Key(),Iter->Value.Func.Param);
			break;
		default:
			return false;
		}
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
int TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::GetStringA(VALUE_TYPE Address,PSTR szBuffer,int MaxLen)
{
	CHAR Value;
	int Length=0;
	while(Length<MaxLen)
	{
		Value=(CHAR)GetPtrValue(Address+(VALUE_TYPE)Length);
		if(Value==0)
			break;
		szBuffer[Length]=Value;
		Length++;
	}
	szBuffer[Length]=0;
	return Length;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
int TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::GetStringW(VALUE_TYPE Address,PWSTR szBuffer,int MaxLen)
{
	WCHAR Value;
	int Length=0;
	while(Length<MaxLen)
	{
		Value=(WCHAR)GetPtrValue(Address+(VALUE_TYPE)Length*2);
		if(Value==0)
			break;
		szBuffer[Length]=Value;
		Length++;
	}
	szBuffer[Length]=0;
	return Length;	
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
void TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::GetMem(VALUE_TYPE Address,BYTE* Buffer,int Len)
{
	int Length=0;
	while(Length<Len)
	{
		Buffer[Length]=(BYTE)GetPtrValue(Address+(VALUE_TYPE)Length);
		Length++;
	}
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Null(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	return NULL;
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::PtrValue(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(0,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT NextIter;
	NextIter = OptIter+1;
	OptIter->Value.Value = pThis->GetPtrValue(NextIter->Value.Value);
	pThis->RemoveCalcItem(NextIter,1,ExpItemList);
	return &(*OptIter);	
}


template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::LogicAnd(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value && NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}


template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::LogicOr(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value || NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::LogicXor(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	if(PrevIter->Value.Value && !NextIter->Value.Value)
		PrevIter->Value.Value=true;
	else if(!PrevIter->Value.Value && NextIter->Value.Value)
		PrevIter->Value.Value=true;
	else
		PrevIter->Value.Value=false;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::NotBelow(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value >= NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::NotAbove(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value <= NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Below(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value < NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Above(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value > NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Equal(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	STExpItemListIT PrevIter,NextIter;
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
	{
		PrevIter = OptIter-1;
		if(PrevIter == ExpItemList.End())
			return NULL;
		NextIter = OptIter+1;
		if(NextIter == ExpItemList.End())
			return NULL;
		STExpItemListIT StrIter,PtrIter;
		if(PrevIter->Type == STExpItem::STR && NextIter->Type == STExpItem::RESULT)
		{
			StrIter = PrevIter;
			PtrIter = NextIter;
		}
		else if(PrevIter->Type == STExpItem::RESULT && NextIter->Type == STExpItem::STR)
		{
			StrIter = NextIter;
			PtrIter = PrevIter;
		}
		else
			return NULL;
		BYTE szBuffer[64];
		pThis->GetMem(PtrIter->Value.Value,szBuffer,MIN(StrIter->Length*2,sizeof(szBuffer)));
		VALUE_TYPE Result=1;
		if(TStrNICmp((PCSTR)szBuffer,StrIter->Value.pStr,MIN(StrIter->Length,sizeof(szBuffer))))
		{
			if(TStrNICmp((PCWSTR)szBuffer,StrIter->Value.pStr,MIN(StrIter->Length,sizeof(szBuffer)/2)))
				Result=0;
		}
		PrevIter->Type = STExpItem::RESULT;
		PrevIter->Value.Value = Result;
		pThis->RemoveCalcItem(OptIter,2,ExpItemList);
		return &(*PrevIter);
	}
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value == NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::NotEqual(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value != NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::ShiftRight(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value >> NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::ShiftLeft(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value << NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Add(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value + NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Sub(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
	{
		if(pThis->CheckCalcItem(0,OptIter,1,ExpItemList)==false)
			return NULL;
		STExpItemListIT NextIter;
		NextIter = OptIter+1;
		OptIter->Value.Value=(VALUE_TYPE)(0-NextIter->Value.Value);
		pThis->RemoveCalcItem(NextIter,1,ExpItemList);
		return &(*OptIter);
	}
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value - NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Mul(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	STExpItemListIT PrevIter,NextIter;
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
	{
		if(pThis->CheckCalcItem(0,OptIter,1,ExpItemList)==false)
			return NULL;
		STExpItemListIT NextIter;
		NextIter = OptIter+1;
		OptIter->Value.Value=pThis->GetPtrValue(NextIter->Value.Value);
		pThis->RemoveCalcItem(NextIter,1,ExpItemList);
		return &(*OptIter);
	}
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value * NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Div(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	if(NextIter->Value.Value==0)
		return NULL;
	PrevIter->Value.Value=PrevIter->Value.Value / NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Mod(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value % NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Xor(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value ^ NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Not(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(0,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT NextIter;
	NextIter = OptIter+1;
	OptIter->Value.Value=!NextIter->Value.Value;
	pThis->RemoveCalcItem(NextIter,1,ExpItemList);
	return &(*OptIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::And(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value & NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::Or(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	if(pThis->CheckCalcItem(1,OptIter,1,ExpItemList)==false)
		return NULL;
	STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	PrevIter->Value.Value=PrevIter->Value.Value | NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::LeftBracket(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	int	BracketStack;
	STExpItemListIT BeginIter,EndIter;
	BeginIter = OptIter+1;
	BracketStack = 0;
	EndIter=BeginIter;
	while(EndIter!=ExpItemList.End())
	{
		if(TStrNCmp(EndIter->ItemStr,"(",EndIter->Length)==0)
			BracketStack++;
		if(TStrNCmp(EndIter->ItemStr,")",EndIter->Length)==0)
		{
			if(BracketStack)
				BracketStack--;
			else
				break;
		}
		EndIter++;
	}
	if(EndIter==ExpItemList.End())
		return NULL;
	STExpItemList BracketExpItemList;
	ExpItemList.Move(BeginIter,EndIter,BracketExpItemList,BracketExpItemList.Begin());
	if(pThis->CalcItem(BracketExpItemList.Begin(),BracketExpItemList)==false)
		return false;
	OptIter->Value.Value = BracketExpItemList.Begin()->Value.Value;
	BeginIter = OptIter+1;
	pThis->RemoveCalcItem(BeginIter,1,ExpItemList);
	return &(*OptIter);
}

template<class CHAR_TYPE,class VALUE_TYPE,bool bIgnoreCase>
TExpItem<CHAR_TYPE,VALUE_TYPE>*TExpCalc<CHAR_TYPE,VALUE_TYPE,bIgnoreCase>::NonOptr(STExpItemListIT&OptIter,STExpItemList&ExpItemList,TExpCalc*pThis)
{
	return NULL;
}

ALT_NAME_SPACE_END

#endif

