///////////////////////////////////////////////////////////////////////////////
//Array
//Coded by Finaldoom
//动态数组
//作者：陈俊豪
///////////////////////////////////////////////////////////////////////////////
#ifndef _ALT_ARRAY_HPP_
#define _ALT_ARRAY_HPP_

ALT_NAME_SPACE_BEGIN

template<class VALUE,int SIZE = 0>
class TArray : public ALTObj<VALUE>
{
public:
	int		m_Count;
	int		m_Size;
protected:
	VALUE*	m_ValueAry;
public:
	TArray()
	{
		m_Count=m_Size=0;
		m_ValueAry = NULL;
		Resize(SIZE);
	}
	TArray(const TArray&Obj)
	{
		CopyConstruct(Obj);
	}
	TArray(VALUE*pValueAry,int m_Count)
	{
		Attach(pValueAry,m_Count);
	}
	~TArray()
	{
		if(m_ValueAry)
		{
			DestructArray(m_ValueAry);
			m_ValueAry = NULL;
		}
		m_Count=m_Size=0;
	}
	void CopyConstruct(const TArray&Obj)
	{
		m_ValueAry = NULL;
		m_Count=m_Size=0;
		Resize(Obj.m_Size);
		for(int n=0;n<Obj.m_Count;n++)
			Append(Obj[n]);
	}
public:
	inline int Size(){return m_Size;}
	inline int Count(){return m_Count;}
	void Clear()
	{
		int OldSize = m_Size;
		if(m_ValueAry)
		{
			DestructArray(m_ValueAry);
			m_ValueAry = NULL;
		}
		m_Count=m_Size=0;
		Resize(OldSize);
	}
	bool Resize(int NewSize)
	{
		if(NewSize==m_Size)
			return true;
		if(m_ValueAry)
		{
			DestructArray(m_ValueAry);
			m_ValueAry = NULL;
		}
		m_Size = NewSize;
		if(m_Size)
			m_ValueAry = ConstructArray(m_Size);
		m_Count=0;
		return true;
	}
	VALUE* Append(const VALUE&Value = *(VALUE*)NULL)
	{
		if(m_Count>=m_Size)
			Resize(m_Size*2);
		if(&Value)
			m_ValueAry[m_Count]=Value;
		m_Count++;
		return &m_ValueAry[m_Count-1];
	}
	operator VALUE*() const
	{
		return m_ValueAry;
	}
	bool Remove()
	{
		if(m_Count<=0)
			return false;
		m_Count--;
		return true;
	}
	inline VALUE& operator[](int n)const
	{
		return m_ValueAry[n];
	}
	void operator=(const TArray&Obj)
	{
		Clear();
		CopyConstruct(Obj);
	}
	void Attach(VALUE*pValueAry,int m_Count)
	{
		Clear();
		if(m_ValueAry)
		{
			DestructArray(m_ValueAry);
			m_ValueAry = NULL;
		}
		m_ValueAry = pValueAry;
		m_Count = m_Count;
		m_Size = SIZE;
	}
	void Detach()
	{
		m_ValueAry = NULL;
		m_Count = 0;
		m_Size = 0;
	}
	int Find(const VALUE&Value)
	{
		int Index,n;
		n = m_Count;
		Index = 0;
		while(n)
		{
			if(n%2)
				n++;
			n/=2;
			Index+=n;
			if(Value==m_ValueAry[Index])
				return Index;
			if(Value<m_ValueAry[Index])
				Index-=n;
		}
		return -1;
	}
public:
	int	Save(ALTFileStream&Stream)
	{
		int Length;
		Length=Stream.Puts(&m_Size,sizeof(m_Size));
		Length+=Stream.Puts(&m_Count,sizeof(m_Count));
		for(int n=0;n<m_Count;n++)
			Length+=ALTArchiveType::Save(Stream,&m_ValueAry[n],sizeof(VALUE));
		return Length;
	}
	int	Load(ALTFileStream&Stream)
	{
		int TotalLength,Length,Num;
		Clear();
		TotalLength = 0;
		Length=Stream.Gets(&Num,sizeof(Num));
		if(Length!=sizeof(Num))
			return 0;
		TotalLength+=Length;
		Resize(Num);
		Length=Stream.Gets(&Num,sizeof(Num));
		if(Length!=sizeof(Num))
			return 0;
		TotalLength+=Length;
		for(int n=0;n<Num;n++)
		{
			Length=Append()->Load(Stream);
			if(Length==0)
				return 0;
			TotalLength+=Length;
		}
		return TotalLength;
	}
};

ALT_NAME_SPACE_END

#endif

