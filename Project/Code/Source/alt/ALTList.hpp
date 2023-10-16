///////////////////////////////////////////////////////////////////////////////
//List
//Coded by Finaldoom
//链表
//作者：陈俊豪
///////////////////////////////////////////////////////////////////////////////
#ifndef _ALT_LIST_HPP
#define _ALT_LIST_HPP

ALT_NAME_SPACE_BEGIN

template<class VALUE>
class TListNode;

template<class VALUE>
class TListNodeBase
{
public:
	typedef TListNode<VALUE>*	NODE_PTR;
	NODE_PTR	pNext;
	NODE_PTR	pPrev;
};

template<class VALUE>
class TListNode : public TListNodeBase<VALUE>
{
public:
	VALUE		Value;
};

template<class VALUE>
class TListIter
{
public:
	typedef TListNode<VALUE>	NODE;
	NODE*	pNode;
public:
	inline	TListIter(){pNode = NULL;}
	inline	TListIter(NODE*pNewNode){pNode=pNewNode;}
	inline	TListIter(const VALUE&Value){ pNode= (NODE*)((char*)&Value - (char*)&((NODE*)NULL)->Value); }
	inline	void operator++(int){pNode = pNode->pNext;}
	inline	void operator--(int){pNode = pNode->pPrev;}
	inline	void operator+=(int n);
	inline	void operator-=(int n);
	inline	TListIter<VALUE> operator+(int n)const{TListIter<VALUE> Iter;Iter=pNode;Iter+=n;return Iter;}
	inline	TListIter<VALUE> operator-(int n)const{TListIter<VALUE> Iter;Iter=pNode;Iter-=n;return Iter;}
	inline	VALUE* operator->()const{ return &pNode->Value;	}
	inline	VALUE& operator*()const{ return pNode->Value;	}
	inline	bool operator==(NODE*pCmpNode){ return pNode == pCmpNode; }
	inline	bool operator!=(NODE*pCmpNode){ return pNode != pCmpNode; }
	inline	bool operator==(const TListIter&Iter){ return pNode == Iter.pNode; }
	inline	bool operator!=(const TListIter&Iter){ return pNode != Iter.pNode; }
};

template<class VALUE = ALTArchive>
class TList : public ALTObj<TListNode<VALUE> >
{
public:
	typedef TListNodeBase<VALUE>	NODE_BASE;
	typedef TListNode<VALUE>		NODE;
	typedef TListIter<VALUE>		IT;
protected:
	NODE_BASE	m_Head;
	NODE*		m_pHead;
	int			m_Count;
public:
	TList();
	TList(const TList&Obj);
	~TList();
	void	Init();
public:
	inline	int	Count()const {	return m_Count;	}
	inline	IT	Begin()const{return IT(m_pHead->pNext);}
	inline	IT	End()const{return IT(m_pHead);}
	inline	IT	Last()const{return IT(m_pHead->pPrev);}
	inline	IT	operator[](int n)const;
	TList&	operator=(const TList&Obj);
	void	Clear();
	IT		Find(const VALUE&Value);
	IT		Append(const VALUE&Value = *(VALUE*)NULL);
	IT		InsertAfter(const IT&Iter,const VALUE&Value = *(VALUE*)NULL);
	IT		InsertBefore(const IT&Iter,const VALUE&Value = *(VALUE*)NULL);
	IT		Remove(const IT&Iter);
	IT		Remove(const IT&BeginIter,const IT&EndIter);
	int		Move(const IT&BeginIter,const IT&EndIter,TList&Obj,const IT&NewBeginIter);
	int		Copy(const IT&BeginIter,const IT&EndIter,TList&Obj,const IT&NewBeginIter);
	int		Save(ALTFileStream&Stream);
	int		Load(ALTFileStream&Stream);
};

//////////////////////////////////////////////////////////////////////////////
//TListIter
//////////////////////////////////////////////////////////////////////////////
template<class VALUE>
void TListIter<VALUE>::operator+=(int n)
{
	while(n>0)
	{
		pNode = pNode->pNext;
		n--;
	}
}

template<class VALUE>
void TListIter<VALUE>::operator-=(int n)
{
	while(n>0)
	{
		pNode = pNode->pPrev;
		n--;
	}
}

//////////////////////////////////////////////////////////////////////////////
//TList
//////////////////////////////////////////////////////////////////////////////
template<class VALUE>
void TList<VALUE>::Init()
{
	m_pHead = (NODE*)&m_Head;
	m_Head.pPrev = m_Head.pNext = m_pHead;
	m_Count = 0;
}

template<class VALUE>
TList<VALUE>::TList()
{
	Init();
}

template<class VALUE>
TList<VALUE>::TList(const TList<VALUE>&Obj)
{
	Init();
	for(IT Iter=Obj.Begin();Iter!=Obj.End();Iter++)
		Append(*Iter);
}

template<class VALUE>
TList<VALUE>::~TList()
{
	Clear();
}

template<class VALUE>
void TList<VALUE>::Clear()
{
	NODE*pDelNode,*pNextNode = m_pHead->pNext;
	while(pNextNode!=m_pHead)
	{
		pDelNode = pNextNode;
		pNextNode=pNextNode->pNext;
		Destruct(pDelNode);
	}
	Init();
}

template<class VALUE>
TListIter<VALUE> TList<VALUE>::operator[](int n)const
{
	IT Iter;
	if(n==m_Count-1)
		return Last();
	if(n>=m_Count)
		return End();
	Iter = m_pHead->pNext;
	if(n>0)
		return Iter+n;
	else
		return Iter-(-n);
}

template<class VALUE>
TList<VALUE>& TList<VALUE>::operator=(const TList&Obj)
{
	Clear();
	if(Obj.Count())
	{
		for(IT Iter = Obj.Begin();Iter!=Obj.End();Iter++)
			Append(*Iter);
	}
	return (*this);
}

template<class VALUE>
TListIter<VALUE> TList<VALUE>::Find(const VALUE&Value)
{
	IT Iter(m_pHead->pNext);
	while(Iter!=m_pHead)
	{
		if(Value == Iter.pNode->Value)
			break;
		Iter++;
	}
	return Iter;
}

template<class VALUE>
TListIter<VALUE> TList<VALUE>::Append(const VALUE&Value)
{
	IT Iter;
	Iter.pNode=Construct();
	if(&Value)
		Iter.pNode->Value = Value;
	if(m_Count==0)
		m_pHead->pNext=Iter.pNode;
	Iter.pNode->pNext = m_pHead;
	Iter.pNode->pPrev = m_pHead->pPrev;
	Iter.pNode->pPrev->pNext = Iter.pNode;
	m_pHead->pPrev=Iter.pNode;
	m_Count++;
	return Iter;
}

template<class VALUE>
TListIter<VALUE> TList<VALUE>::InsertAfter(const IT&Iter,const VALUE&Value)
{
	IT NewIter;
	NewIter.pNode =Construct();
	if(&Value)
		NewIter.pNode->Value=Value;
	NewIter.pNode->pNext=Iter.pNode->pNext;
	NewIter.pNode->pPrev=Iter.pNode;
	Iter.pNode->pNext->pPrev = NewIter.pNode;
	Iter.pNode->pNext=NewIter.pNode;
	m_Count++;
	return NewIter;
}

template<class VALUE>
TListIter<VALUE> TList<VALUE>::InsertBefore(const IT&Iter,const VALUE&Value)
{
	IT NewIter(Iter.pNode->pPrev);
	return InsertAfter(NewIter,Value);
}

template<class VALUE>
TListIter<VALUE> TList<VALUE>::Remove(const IT&Iter)//根据迭代器删除一个节点
{
	NODE*pPrev;
	if(Iter.pNode == m_pHead)
		return (IT&)m_pHead;
	Iter.pNode->pPrev->pNext = Iter.pNode->pNext;
	Iter.pNode->pNext->pPrev = Iter.pNode->pPrev;
	pPrev = Iter.pNode->pPrev;
	Destruct(Iter.pNode);
	m_Count--;
	return pPrev;
}

template<class VALUE>
TListIter<VALUE> TList<VALUE>::Remove(const IT&BeginIter,const IT&EndIter)
{
	NODE*pPrev = BeginIter.pNode->pPrev;
	for(IT Iter= BeginIter;Iter!=EndIter;Iter++)
		Iter = Remove(Iter);
	return pPrev;
}

template<class VALUE>
int TList<VALUE>::Move(const IT&BeginIter,const IT&EndIter,TList&Obj,const IT&NewBeginIter)
{
	NODE*pBegin,*pLast;
	int Count=0;
	for(IT Iter=BeginIter;Iter!=EndIter;Iter++)
		Count++;
	if(Count==0)
		return Count;
	pBegin = BeginIter.pNode;
	pLast = EndIter.pNode->pPrev;

	BeginIter.pNode->pPrev->pNext = EndIter.pNode;	
	EndIter.pNode->pPrev = pBegin->pPrev;
	m_Count-=Count;

	pBegin->pPrev = NewBeginIter.pNode;
	pLast->pNext = NewBeginIter.pNode->pNext;

	NewBeginIter.pNode->pNext = pBegin;
	pLast->pNext->pPrev = pLast;
	Obj.m_Count+=Count;
	return Count;
}

template<class VALUE>
int TList<VALUE>::Copy(const IT&BeginIter,const IT&EndIter,TList&Obj,const IT&NewBeginIter)
{
	int Count=0;
	IT NewIter = NewBeginIter;
	for(IT Iter=BeginIter;Iter!=EndIter;Iter++)
	{
		NewIter = Obj.InsertAfter(NewIter,*Iter);
		Count++;
	}
	return Count;
}


template<class VALUE>
int	TList<VALUE>::Save(ALTFileStream&Stream)
{
	int Length=Stream.Puts(&m_Count,sizeof(m_Count));
	for(IT Iter= Begin();Iter!=End();Iter++)
		Length+=Iter->Save(Stream);
	return Length;
}

template<class VALUE>
int	TList<VALUE>::Load(ALTFileStream&Stream)
{
	int TotalLength,Length,Count;
	IT Iter;
	Clear();
	TotalLength = 0;
	Length=Stream.Gets(&Count,sizeof(Count));
	if(Length!=sizeof(Count))
		return 0;
	TotalLength+=Length;
	while(Count>0)
	{
		Iter = Append();
		Length=Iter->Load(Stream);
		if(Length==0)
			return 0;
		TotalLength+=Length;
		Count--;
	}
	return TotalLength;
}

ALT_NAME_SPACE_END

#endif
