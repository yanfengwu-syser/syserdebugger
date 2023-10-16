///////////////////////////////////////////////////////////////////////////////
//Map (Red-Black Tree)
//Coded by Finaldoom
//集合 (没有值的唯一Map)
//作者：陈俊豪
#ifndef _ALT_SET_HPP_
#define _ALT_SET_HPP_

ALT_NAME_SPACE_BEGIN

template<class KEY>
class TSetIter : public TMapIter<KEY,ALT_EMPTY_STRUCT>
{
public:
	typedef TMapNode<KEY,ALT_EMPTY_STRUCT>	NODE;
public:
	inline	TSetIter(){ pNode = NULL;}
	inline	TSetIter(NODE*pOther){ pNode = pOther;}
	inline	TSetIter(const KEY&Key){ pNode= (NODE*)((char*)&Key - (char*)&((NODE*)NULL)->Key); }
	void	operator++(int){ Increment();}
	void	operator--(int){ Decrement();}
	void	operator++(){ Increment();}
	void	operator--(){ Decrement();}
	inline	void	operator+=(int n);
	inline	void	operator-=(int n);
	inline	TSetIter operator+(int n)const{TSetIter Iter;Iter=pNode;Iter+=n;return Iter;}
	inline	TSetIter operator-(int n)const{TSetIter Iter;Iter=pNode;Iter-=n;return Iter;}
	inline	KEY*	operator->()const{ return &pNode->Key;}
	inline	KEY&	operator*()const{ return pNode->Key;}
	inline	bool	operator==(NODE*pOther){ return pNode == pOther; }
	inline	bool	operator!=(NODE*pOther){ return pNode != pOther; }
	inline	bool	operator==(const TSetIter&Iter){ return pNode == Iter.pNode; }
	inline	bool	operator!=(const TSetIter&Iter){ return pNode != Iter.pNode; }
};

template<class KEY>
class TSet : public TMap<KEY,ALT_EMPTY_STRUCT>
{
public:
	typedef TSetIter<KEY>	IT;
public:
	inline	IT&	Begin()const{return *(IT*)&m_pHead->pLeft;}
	inline	IT&	End()const{return *(IT*)&m_pHead;}
	inline	IT&	Last()const{return *(IT*)&m_pHead->pRight;}
	inline	IT	operator[](int n);
	inline	IT	Insert(const KEY&Key){ return *(IT*)&InsertUnique(Key);}
	inline	IT	Find(const KEY&Key){ return *(IT*)&TMap<KEY,ALT_EMPTY_STRUCT>::Find(Key);}
	inline	IT	FindAlmost(const KEY&Key){ return *(IT*)&TMap<KEY,ALT_EMPTY_STRUCT>::FindAlmost(Key);}
};

template<class KEY>
TSetIter<KEY> TSet<KEY>::operator[](int n)
{
	IT Iter;
	Iter = Begin();
	return Iter+n;
}

/*
void test()
{
	int Num;
	TSet<int> SetObj;
	TArray<int,0x1000> NumAry;
	InitStaticRandom(0x10000000);
	for(int n=0;n<NumAry.Size();n++)
	{
		Num = (int)GetStaticRandom(0,0x7FFFFFFF);
		NumAry.Append(Num);
		SetObj.Insert(Num);
	}
	for(int n=0;n<NumAry.Size();n++)
	{
		SetObj.Remove(NumAry[n]);
	}
}
*/

ALT_NAME_SPACE_END

#endif
