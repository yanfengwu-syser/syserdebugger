///////////////////////////////////////////////////////////////////////////////
//Map (Red-Black Tree)
//Coded by Finaldoom
//映射 (红黑树)
//作者：陈俊豪
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//取节点个数	int	Count();
//返回值:	节点个数
///////////////////////////////////////////////////////////////////////////////
//取最小值	IT	Begin();
//返回值:	最小值指示器
///////////////////////////////////////////////////////////////////////////////
//取最大值	IT	Last();	
//返回值:	最大值指示器
///////////////////////////////////////////////////////////////////////////////
//取最大值	IT	End();	
//返回值:	无效值指示器
///////////////////////////////////////////////////////////////////////////////
//删除所有节点	void	Clear();
///////////////////////////////////////////////////////////////////////////////
//唯一插入	IT	InsertUnique(const KEY&Key,const VALUE&Value);
//重复插入	IT	InsertEqual(const KEY&Key,const VALUE&Value);
//参数	const KEY&Key		:	关键字
//参数	const VALUE&Value	:	值
//返回值:	插入位置的指示器
///////////////////////////////////////////////////////////////////////////////
//删除指定节点	void	Remove(const IT&Iter);
//参数	const IT&Iter	:	指示器
///////////////////////////////////////////////////////////////////////////////
//删除所有Key节点	int	Remove(const KEY&Key);
//参数	const KEY&Key	:	关键字
//返回值:	删除的节点个数
///////////////////////////////////////////////////////////////////////////////
//查找Key节点	IT	Find(const KEY&Key);
//参数	const KEY&Key	:	关键字
//返回值:	节点指示器
///////////////////////////////////////////////////////////////////////////////

#ifndef _ALT_MAP_HPP_
#define _ALT_MAP_HPP_

ALT_NAME_SPACE_BEGIN

template<class KEY,class VALUE>
class TMapNode;

template<class KEY,class VALUE>
class TMapNodeBase
{
public:
	enum	COLOR{RB_BLACK,RB_RED};
	typedef TMapNode<KEY,VALUE>	NODE;
public:
	NODE*	pLeft;
	NODE*	pRight;
	NODE*	pParent;
	COLOR	Color;
	bool	bNode;
};

template<class KEY,class VALUE>
class TMapNode : public TMapNodeBase<KEY,VALUE>
{
public:
	KEY			Key;
	VALUE		Value;
	bool inline	IsHead(){ return !bNode;}
	bool inline	IsNode(){ return bNode;}
};

template<class KEY,class VALUE>
class TMapIter
{
public:
	typedef TMapNode<KEY,VALUE>	NODE;
	NODE*	pNode;
public:
	inline	TMapIter(){ pNode = NULL;}
	inline	TMapIter(NODE*pOther){ pNode = pOther;}
	inline	TMapIter(const VALUE&Value){ pNode= (NODE*)((char*)&Value - (char*)&((NODE*)NULL)->Value); }
	void	operator++(int){ Increment();}
	void	operator--(int){ Decrement();}
	void	operator++(){ Increment();}
	void	operator--(){ Decrement();}
	inline	void	operator+=(int n);
	inline	void	operator-=(int n);
	inline	TMapIter operator+(int n)const{TMapIter Iter;Iter=pNode;Iter+=n;return Iter;}
	inline	TMapIter operator-(int n)const{TMapIter Iter;Iter=pNode;Iter-=n;return Iter;}
	inline	VALUE*	operator->()const{ return &pNode->Value;}
	inline	VALUE&	operator*()const{ return pNode->Value;}
	inline	bool	operator==(NODE*pOther){ return pNode == pOther; }
	inline	bool	operator!=(NODE*pOther){ return pNode != pOther; }
	inline	bool	operator==(const TMapIter&Iter){ return pNode == Iter.pNode; }
	inline	bool	operator!=(const TMapIter&Iter){ return pNode != Iter.pNode; }
	inline	KEY&	Key()const{	return pNode->Key;}
	inline	bool	IsExist(){	return pNode && pNode->IsNode();}
protected:
	void	Increment();
	void	Decrement();
};

template<class KEY,class VALUE = ALT_EMPTY_STRUCT>
class TMap : public ALTObj<TMapNode<KEY,VALUE> >
{
public:
	typedef TMapNodeBase<KEY,VALUE>			NODE_BASE;
	typedef TMapNode<KEY,VALUE>				NODE;
	typedef TMapIter<KEY,VALUE>				IT;
protected:
	NODE_BASE	m_Head;
	NODE*	m_pRoot;
	NODE*	m_pHead;
public:
	int		m_Count;
	TMap();
	TMap(const TMap&Obj);
	~TMap();
	inline	int	Count()const{return m_Count;}
	inline	IT	Begin()const{return IT(m_pHead->pLeft);}
	inline	IT	End()const{return IT(m_pHead);}
	inline	IT	Last()const{return IT(m_pHead->pRight);}
	inline	IT	operator[](int n);
	IT		InsertUnique(const KEY&Key,const VALUE&Value = *(VALUE*)NULL);
	IT		InsertEqual(const KEY&Key,const VALUE&Value = *(VALUE*)NULL);
	IT		Find(const KEY&Key);
	IT		FindAlmost(const KEY&Key);
	TMap&	operator=(const TMap&Obj);
	void	Clear();
	void	Remove(const IT&Iter);
	int		Remove(const KEY&Key);
	int		Index(const IT&Iter);
	int		Save(ALTFileStream&Stream);
	int		Load(ALTFileStream&Stream);
private:
	void	Init();
	void	RotateLeft(NODE*pRotate);
	void	RotateRight(NODE*pRotate);
	void	RemoveTree(NODE*pNode);
	IT		Insert(bool bAddLeft,NODE*pParent,const KEY&Key,const VALUE*pValue);
};

/////////////////////////////////////////////////////////////////////////////
//TMapIter
/////////////////////////////////////////////////////////////////////////////
template<class KEY,class VALUE>
void TMapIter<KEY,VALUE>::Increment()
{
	NODE*pParent;
	if(pNode==NULL)
		return;
	if(pNode->IsHead())
	{
		pNode = pNode->pLeft;
	}
	else if(pNode->pRight->IsNode())
	{
		pNode = pNode->pRight;
		while(pNode->pLeft->IsNode())
			pNode = pNode->pLeft;
	}
	else
	{
		while((pParent = pNode->pParent)->IsNode() && pNode == pParent->pRight)
			pNode = pParent;
		pNode = pParent;
	}
}

template<class KEY,class VALUE>
void TMapIter<KEY,VALUE>::Decrement()
{
	NODE*pParent;
	if(pNode==NULL)
		return;
	if(pNode->IsHead())
	{
		pNode = pNode->pRight;
	}
	else if(pNode->pLeft->IsNode())
	{
		pNode=pNode->pLeft;
		while(pNode->pRight->IsNode())
			pNode = pNode->pRight;
	}
	else
	{
		while((pParent = pNode->pParent)->IsNode() && pNode == pParent->pLeft)
			pNode = pParent;
		pNode = pParent;
	}
}

template<class KEY,class VALUE>
void TMapIter<KEY,VALUE>::operator+=(int n)
{
	while(n>0)
	{
		(*this)++;
		n--;
	}
}

template<class KEY,class VALUE>
void TMapIter<KEY,VALUE>::operator-=(int n)
{
	TMapIter Iter = *this;
	while(n>0)
	{
		(*this)--;
		n--;
	}
}

/////////////////////////////////////////////////////////////////////////////
//TMap
/////////////////////////////////////////////////////////////////////////////
template<class KEY,class VALUE>
void TMap<KEY,VALUE>::Init()
{
	m_Head.Color = NODE::RB_BLACK;
	m_Head.bNode = false;
	m_pHead = (NODE*)&m_Head;
	m_pRoot = m_Head.pParent = m_Head.pLeft = m_Head.pRight = m_pHead;
	m_Count = 0;
}

template<class KEY,class VALUE>
TMap<KEY,VALUE>::TMap()
{
	Init();
}

template<class KEY,class VALUE>
TMap<KEY,VALUE>::TMap(const TMap&Obj)
{
	Init();
	for(IT It = Obj.Begin();It!=Obj.End();It++)
		InsertEqual(It.Key(),*It);
}

template<class KEY,class VALUE>
TMap<KEY,VALUE>::~TMap()
{
	Clear();
}

template<class KEY,class VALUE>
void TMap<KEY,VALUE>::Clear()
{
	if(m_Count)
	{
		RemoveTree(m_pRoot);
		Init();
	}
}

template<class KEY,class VALUE>
int TMap<KEY,VALUE>::Remove(const KEY&Key)
{	
	IT Iter,DelIter;
	int RemoveCount = 0;
	Iter = Find(Key);
	while(Iter!=End() && Iter.Key() == Key)
	{
		DelIter = Iter;
		Iter++;
		RemoveCount++;
		Remove(DelIter);
	}
	return RemoveCount;
}

template<class KEY,class VALUE>
void TMap<KEY,VALUE>::Remove(const IT&Iter)
{
	NODE* pErasedNode,*pFixNode,*pFixNodeParent,*pNode;
	pNode = pErasedNode = Iter.pNode;
	if(pNode->pLeft->IsHead())
		pFixNode = pNode->pRight;
	else if(pNode->pRight->IsHead())
		pFixNode = pNode->pLeft;
	else
	{
		IT NextIter(Iter.pNode);
		NextIter++;
		pNode = NextIter.pNode;
		pFixNode = pNode->pRight;
	}
	if (pNode == pErasedNode)
	{
		pFixNodeParent = pErasedNode->pParent;
		if(pFixNode->IsNode())
			pFixNode->pParent = pFixNodeParent;
		if(m_pRoot == pErasedNode)
			m_pRoot = pFixNode;
		else if(pFixNodeParent->pLeft == pErasedNode)
			pFixNodeParent->pLeft = pFixNode;
		else
			pFixNodeParent->pRight = pFixNode;

		if(m_pHead->pLeft == pErasedNode)
		{
			if(pFixNode->IsNode())
			{
				m_pHead->pLeft = pFixNode;
				while(m_pHead->pLeft->pLeft->IsNode())
					m_pHead->pLeft = m_pHead->pLeft->pLeft;
			}
			else
				m_pHead->pLeft = pFixNodeParent;
		}
		if (m_pHead->pRight == pErasedNode)
		{
			if(pFixNode->IsNode())
			{
				m_pHead->pRight = pFixNode;
				while(m_pHead->pRight->pRight->IsNode())
					m_pHead->pRight = m_pHead->pRight->pRight;
			}
			else
				m_pHead->pRight = pFixNodeParent;
		}
	}
	else
	{
		pErasedNode->pLeft->pParent = pNode;
		pNode->pLeft = pErasedNode->pLeft;

		if (pNode == pErasedNode->pRight)
			pFixNodeParent = pNode;
		else
		{
			pFixNodeParent = pNode->pParent;
			if(pFixNode->IsNode())
				pFixNode->pParent = pFixNodeParent;
			pFixNodeParent->pLeft = pFixNode;
			pNode->pRight = pErasedNode->pRight;
			pErasedNode->pRight->pParent = pNode;
		}
		if (m_pRoot == pErasedNode)
			m_pRoot = pNode;
		else if (pErasedNode->pParent->pLeft == pErasedNode)
			pErasedNode->pParent->pLeft = pNode;
		else
			pErasedNode->pParent->pRight = pNode;

		pNode->pParent = pErasedNode->pParent;
		NODE_BASE SwapNode;
		SwapNode.Color	= pNode->Color;
		pNode->Color = pErasedNode->Color;
		pErasedNode->Color = SwapNode.Color;
	}
	//Balance
	if(pErasedNode->Color == NODE::RB_BLACK)
	{
		for(;pFixNode != m_pRoot && pFixNode->Color == NODE::RB_BLACK ; pFixNodeParent = pFixNode->pParent)
		{
			if(pFixNode == pFixNodeParent->pLeft)
			{
				pNode = pFixNodeParent->pRight;
				if (pNode->Color == NODE::RB_RED)
				{
					pNode->Color = NODE::RB_BLACK;
					pFixNodeParent->Color = NODE::RB_RED;
					RotateLeft(pFixNodeParent);
					pNode = pFixNodeParent->pRight;
				}
				if(pNode->IsHead())
					pFixNode = pFixNodeParent;// shouldn't happen
				else if(pNode->pLeft->Color == NODE::RB_BLACK && pNode->pRight->Color == NODE::RB_BLACK)
				{
					pNode->Color = NODE::RB_RED;
					pFixNode = pFixNodeParent;
				}
				else
				{
					if(pNode->pRight->Color == NODE::RB_BLACK)
					{
						pNode->pLeft->Color = NODE::RB_BLACK;
						pNode->Color = NODE::RB_RED;
						RotateRight(pNode);
						pNode = pFixNodeParent->pRight;
					}
					pNode->Color = pFixNodeParent->Color;
					pNode->pRight->Color = NODE::RB_BLACK;
					pFixNodeParent->Color = NODE::RB_BLACK;
					RotateLeft(pFixNodeParent);
					break;
				}
			}
			else
			{
				pNode = pFixNodeParent->pLeft;
				if(pNode->Color == NODE::RB_RED)
				{
					pNode->Color = NODE::RB_BLACK;
					pFixNodeParent->Color = NODE::RB_RED;
					RotateRight(pFixNodeParent);
					pNode = pFixNodeParent->pLeft;
				}
				if(pNode->IsHead())
					pFixNode = pFixNodeParent;	// shouldn't happen
				else if(pNode->pRight->Color == NODE::RB_BLACK && pNode->pLeft->Color == NODE::RB_BLACK)
				{
					pNode->Color = NODE::RB_RED;
					pFixNode = pFixNodeParent;
				}
				else
				{
					if(pNode->pLeft->Color == NODE::RB_BLACK)
					{
						pNode->pRight->Color = NODE::RB_BLACK;
						pNode->Color = NODE::RB_RED;
						RotateLeft(pNode);
						pNode = pFixNodeParent->pLeft;
					}
					pNode->Color = pFixNodeParent->Color;
					pFixNodeParent->Color = NODE::RB_BLACK;
					pNode->pLeft->Color = NODE::RB_BLACK;
					RotateRight(pFixNodeParent);
					break;
				}
			}			
		}
		pFixNode->Color = NODE::RB_BLACK;
	}
	Destruct(pErasedNode);
	if(0 < m_Count)
		m_Count--;
}

template<class KEY,class VALUE>
void TMap<KEY,VALUE>::RemoveTree(NODE*pNode)
{
	if(pNode->IsHead())
		return;
	if(pNode->pLeft->IsNode())
		RemoveTree(pNode->pLeft);
	if(pNode->pRight->IsNode())
		RemoveTree(pNode->pRight);
	if(m_pRoot==pNode)
		m_pRoot = m_pHead;
	if(pNode->pParent->pLeft==pNode)
		pNode->pParent->pLeft=m_pHead;
	else
		pNode->pParent->pRight=m_pHead;
	if(m_pHead->pLeft == pNode)
	{
		IT It(pNode);
		It++;
		m_pHead->pLeft = It.pNode;
	}
	if(m_pHead->pRight == pNode)
	{
		IT It(pNode);
		It--;
		m_pHead->pLeft = It.pNode;
	}
	m_Count--;
	Destruct(pNode);
}

template<class KEY,class VALUE>
void TMap<KEY,VALUE>::RotateLeft(NODE*pRotate)
{
	NODE*pNode = pRotate->pRight;
	pRotate->pRight = pNode->pLeft;
	if(pNode->pLeft->IsNode())
		pNode->pLeft->pParent = pRotate;
	pNode->pParent = pRotate->pParent;
	if(pRotate == m_pRoot)
		m_pRoot = pNode;
	else if(pRotate == pRotate->pParent->pLeft)
		pRotate->pParent->pLeft = pNode;
	else
		pRotate->pParent->pRight = pNode;
	pNode->pLeft = pRotate;
	pRotate->pParent = pNode;
}

template<class KEY,class VALUE>
void TMap<KEY,VALUE>::RotateRight(NODE*pRotate)
{
	NODE*pNode = pRotate->pLeft;
	pRotate->pLeft = pNode->pRight;
	if(pNode->pRight->IsNode())
		pNode->pRight->pParent = pRotate;
	pNode->pParent = pRotate->pParent;
	if(pRotate == m_pRoot)
		m_pRoot = pNode;
	else if(pRotate == pRotate->pParent->pRight)
		pRotate->pParent->pRight = pNode;
	else
		pRotate->pParent->pLeft = pNode;
	pNode->pRight = pRotate;
	pRotate->pParent = pNode;
}

template<class KEY,class VALUE>
TMapIter<KEY,VALUE> TMap<KEY,VALUE>::operator[](int n)
{
	IT Iter;
	Iter = Begin();
	return Iter+n;
}

template<class KEY,class VALUE>
TMap<KEY,VALUE>& TMap<KEY,VALUE>::operator=(const TMap<KEY,VALUE>&Obj)
{
	Clear();
	if(Obj.Count())
	{
		for(IT It = Obj.Begin();It!=Obj.End();It++)
			InsertEqual(It.Key(),*It);
	}
	return (*this);
}

template<class KEY,class VALUE>
TMapIter<KEY,VALUE> TMap<KEY,VALUE>::InsertUnique(const KEY&Key,const VALUE&Value)
{
	bool bAddLeft = true;
	NODE*pNode,*pParent;
	pParent = m_pHead;
	pNode = m_pRoot;
	while(pNode->IsHead()==false)
	{
		pParent = pNode;
		bAddLeft = Key<pNode->Key;
		pNode = bAddLeft ? pNode->pLeft : pNode->pRight;
	}
	IT  It = pParent;
	if(bAddLeft==false);
	else if (It == Begin())
		return Insert(true,pParent,Key,&Value);
	else
		It--;
	if(It.pNode->Key < Key)
		return Insert(bAddLeft,pParent,Key,&Value);
	else
		return End();
}

template<class KEY,class VALUE>
TMapIter<KEY,VALUE> TMap<KEY,VALUE>::InsertEqual(const KEY&Key,const VALUE&Value)
{
	bool bAddLeft = true;
	NODE*pNode,*pParent;
	pParent = m_pHead;
	pNode = m_pRoot;
	while(pNode->IsNode())
	{
		pParent = pNode;
		bAddLeft = Key<pNode->Key;
		pNode = bAddLeft ? pNode->pLeft : pNode->pRight;
	}
	return Insert(bAddLeft,pParent,Key,&Value);
}

template<class KEY,class VALUE>
TMapIter<KEY,VALUE> TMap<KEY,VALUE>::Insert(bool bAddLeft,NODE*pParent,const KEY&Key,const VALUE*pValue)
{
	NODE* pNew = Construct();
	pNew->Key = Key;
	if(pValue)
		pNew->Value = *pValue;
	pNew->pLeft = pNew->pRight = m_pHead;
	pNew->pParent = pParent;
	pNew->Color = NODE::RB_RED;
	pNew->bNode = true;
	m_Count++;
	if (pParent == m_pHead)
	{
		m_pRoot = pNew;
		m_pHead->pLeft = m_pHead->pRight = pNew;
	}
	else if (bAddLeft)
	{
		pParent->pLeft = pNew;
		if (pParent == m_pHead->pLeft)
			m_pHead->pLeft = pNew;
	}
	else
	{
		pParent->pRight = pNew;
		if (pParent == m_pHead->pRight)
			m_pHead->pRight = pNew;
	}
	NODE*pNode=pNew;
	while(pNode->pParent->Color == NODE::RB_RED)
	{
		if(pNode->pParent == pNode->pParent->pParent->pLeft)
		{
			pParent = pNode->pParent->pParent->pRight;
			if(pParent->Color == NODE::RB_RED)
			{
				pNode->pParent->Color = NODE::RB_BLACK;
				pParent->Color = NODE::RB_BLACK;
				pNode->pParent->pParent->Color = NODE::RB_RED;
				pNode = pNode->pParent->pParent;
			}
			else
			{
				if(pNode == pNode->pParent->pRight)
				{
					pNode = pNode->pParent;
					RotateLeft(pNode);
				}
				pNode->pParent->Color = NODE::RB_BLACK;
				pNode->pParent->pParent->Color = NODE::RB_RED;
				RotateRight(pNode->pParent->pParent);
			}
		}
		else
		{
			pParent = pNode->pParent->pParent->pLeft;
			if(pParent->Color == NODE::RB_RED)
			{
				pNode->pParent->Color = NODE::RB_BLACK;
				pParent->Color = NODE::RB_BLACK;
				pNode->pParent->pParent->Color = NODE::RB_RED;
				pNode = pNode->pParent->pParent;
			}
			else
			{
				if(pNode == pNode->pParent->pLeft)
				{
					pNode = pNode->pParent;
					RotateRight(pNode);
				}
				pNode->pParent->Color = NODE::RB_BLACK;
				pNode->pParent->pParent->Color = NODE::RB_RED;
				RotateLeft(pNode->pParent->pParent);
			}
		}
	}
	m_pRoot->Color = NODE::RB_BLACK;
	return pNew;
}

template<class KEY,class VALUE>
TMapIter<KEY,VALUE>	TMap<KEY,VALUE>::Find(const KEY&Key)
{
	NODE*pNode=m_pRoot;
	NODE*pWhereNode=m_pHead;
	while(pNode->IsNode())
	{
		if(pNode->Key < Key)
		{
			pNode = pNode->pRight;
		}
		else
		{
			pWhereNode = pNode;
			pNode = pNode->pLeft;
		}
	}
	return pWhereNode==m_pHead || Key < pWhereNode->Key ? End():pWhereNode;
}

template<class KEY,class VALUE>
TMapIter<KEY,VALUE>	TMap<KEY,VALUE>::FindAlmost(const KEY&Key)
{
	NODE*pNode=m_pRoot;
	NODE*pWhereNode,*pLastNode;
	pWhereNode=pLastNode=m_pHead;
	while(pNode->IsNode())
	{
		if(pNode->Key < Key)
		{
			pLastNode = pNode;
			pNode = pNode->pRight;
		}
		else
		{
			pWhereNode = pNode;
			pLastNode = pNode;
			pNode = pNode->pLeft;
		}
	}
	if(pWhereNode!=m_pHead && !(Key<pWhereNode->Key))
		return pWhereNode;
	if(pLastNode==m_pHead)
		return End();
	if(pLastNode->Key<Key)
		return pLastNode;
	IT Iter = pLastNode;
	Iter--;
	return Iter==End()?pLastNode:Iter;
}

template<class KEY,class VALUE>
int	TMap<KEY,VALUE>::Index(const IT&Iter)
{
	IT It = Iter;
	int Index = -1;
	while(It!=End())
	{
		Index++;
		It--;
	}
	return Index;
}

template<class KEY,class VALUE>
int	TMap<KEY,VALUE>::Save(ALTFileStream&Stream)
{
	int Length;
	Length=Stream.Puts(&m_Count,sizeof(m_Count));
	for(IT Iter= Begin();Iter!=End();Iter++)
	{
		Length+=Iter.Key().Save(Stream);
		Length+=Iter->Save(Stream);
	}
	return Length;
}

template<class KEY,class VALUE>
int	TMap<KEY,VALUE>::Load(ALTFileStream&Stream)
{
	KEY	Key;
	int TotalLength,Length,Count;
	IT Iter;
	Clear();
	Count = 0;
	TotalLength = 0;
	Length = Stream.Gets(&Count,sizeof(Count));
	if(Length != sizeof(Count))
		return 0;
	TotalLength+=Length;
	while(Count > 0)
	{
		Length = Key.Load(Stream);
		if(Length==0)
			return 0;
		TotalLength+=Length;
		Iter = InsertEqual(Key);
		Length = Iter->Load(Stream);
		if(Length==0)
			return 0;
		TotalLength+=Length;
		Count--;
	}
	return TotalLength;
}

ALT_NAME_SPACE_END

#endif
