///////////////////////////////////////////////////////////////////////////////
//Map (Binary Tree)
//Coded by Finaldoom
//¶þ²æÊ÷
//×÷Õß£º³Â¿¡ºÀ
#ifndef _ALT_BTREE_H_
#define _ALT_BTREE_H_

ALT_NAME_SPACE_BEGIN

template<class VALUE>
class TBTreeNode
{
public:
	VALUE		Value;
	TBTreeNode*	pParentNode;
	TBTreeNode*	pLeftNode;
	TBTreeNode*	pRightNode;
	int			Level;
};

template<class VALUE>
class TBTreeIter
{
public:
	typedef TBTreeNode<VALUE>	NODE;
public:
	NODE*	m_pNode;
	NODE*	m_pLeftNode;
	NODE*	m_pRightNode;
	NODE*	m_pParentNode;
public:
	TBTreeIter(){ m_pNode = m_pParentNode = m_pLeftNode = m_pRightNode = NULL;}
	TBTreeIter(NODE*pNode){ m_pNode = pNode;	Update();}
	void operator++(int){ m_pNode = m_pRightNode;	Update();}
	void operator--(int){ m_pNode = m_pParentNode; Update();}
	void operator++(){ m_pNode = m_pLeftNode;Update();}
	VALUE* operator->(){ return &m_pNode->Value;}
	VALUE& operator*(){ return m_pNode->Value;}
	bool operator==(NODE*pNode){ return m_pNode == pNode; }
	bool operator!=(NODE*pNode){ return m_pNode != pNode; }
	bool operator==(const NODE&Iter){ return m_pNode == Iter.m_pNode; }
	bool operator!=(const NODE&Iter){ return m_pNode != Iter.m_pNode; }
	TBTreeIter GetLeft()const{TBTreeIter Iter(m_pLeftNode);return Iter;}
	TBTreeIter GetRight()const{TBTreeIter Iter(m_pRightNode);return Iter;}
private:
	void Update()
	{
		if(m_pNode)
		{
			m_pParentNode = m_pNode->pParentNode;
			m_pLeftNode = m_pNode->pLeftNode;
			m_pRightNode = m_pNode->pRightNode;
		}
		else
			m_pParentNode = m_pLeftNode = m_pRightNode = NULL;
	}
};

template<class VALUE>
class TBTree
{
public:
	typedef TBTreeNode<VALUE>	NODE;
	typedef TBTreeIter<VALUE>	IT;
public:
	NODE*m_pRootNode;
public:
	TBTree();
	~TBTree();
	void Clear();
	IT Root();
	IT CreateRoot(const VALUE&Value);
	IT InsertLeft(IT&ParentIter,const VALUE&Value);
	IT InsertRight(IT&ParentIter,const VALUE&Value);
	void Remove(const IT&Iter);
	void Remove(const NODE*pNode);
};

/////////////////////////////////////////////////////////////////////////////
//TBTree
/////////////////////////////////////////////////////////////////////////////

template<class VALUE>
TBTree<VALUE>::TBTree()
{
	m_pRootNode = NULL;
}

template<class VALUE>
TBTree<VALUE>::~TBTree()
{
	Clear();
}

template<class VALUE>
void TBTree<VALUE>::Clear()
{
	Remove(m_pRootNode);
	m_pRootNode = NULL;
}

template<class VALUE>
TBTreeIter<VALUE> TBTree<VALUE>::Root()
{
	IT Iter;
	Iter = m_pRootNode;
	return Iter;
}

template<class VALUE>
TBTreeIter<VALUE> TBTree<VALUE>::CreateRoot(const VALUE&Value)
{
	IT Iter;
	m_pRootNode = new NODE;
	m_pRootNode->pParentNode = m_pRootNode->pLeftNode = m_pRootNode->pRightNode = NULL;
	m_pRootNode->Value = Value;
	m_pRootNode->Level = 0;
	Iter = m_pRootNode;
	return Iter;
}

template<class VALUE>
TBTreeIter<VALUE> TBTree<VALUE>::InsertLeft(IT&ParentIter,const VALUE&Value)
{
	IT Iter;
	ParentIter.m_pNode->pLeftNode = new NODE;
	ParentIter.m_pNode->pLeftNode->pParentNode = ParentIter.m_pNode;
	ParentIter.m_pNode->pLeftNode->pLeftNode = ParentIter.m_pNode->pLeftNode->pRightNode = NULL;
	ParentIter.m_pNode->pLeftNode->Value = Value;
	ParentIter.m_pNode->pLeftNode->Level = ParentIter.m_pNode->Level + 1;
	Iter = ParentIter.m_pNode->pLeftNode;
	return Iter;
}

template<class VALUE>
TBTreeIter<VALUE> TBTree<VALUE>::InsertRight(IT&ParentIter,const VALUE&Value)
{
	IT Iter;
	ParentIter.m_pNode->pRightNode = new NODE;
	ParentIter.m_pNode->pRightNode->pParentNode = ParentIter.m_pNode;
	ParentIter.m_pNode->pRightNode->pLeftNode = ParentIter.m_pNode->pRightNode->pRightNode = NULL;
	ParentIter.m_pNode->pRightNode->Value = Value;
	ParentIter.m_pNode->pRightNode->Level = ParentIter.m_pNode->Level + 1;
	Iter = ParentIter.m_pNode->pRightNode;
	return Iter;
}

template<class VALUE>
void TBTree<VALUE>::Remove(const IT&Iter)
{
	Remove(Iter.m_pNode);
}

template<class VALUE>
void TBTree<VALUE>::Remove(const NODE*pNode)
{
	if(pNode==NULL)
		return;
	if(pNode->pLeftNode)
		Remove(pNode->pLeftNode);
	if(pNode->pRightNode)
		Remove(pNode->pRightNode);
	if(m_pRootNode==pNode)
		m_pRootNode = NULL;
	delete pNode;
}

ALT_NAME_SPACE_END

#endif
