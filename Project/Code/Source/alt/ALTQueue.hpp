///////////////////////////////////////////////////////////////////////////////
//Queue
//Coded by Finaldoom
//队列
//作者：陈俊豪
///////////////////////////////////////////////////////////////////////////////
#ifndef _ALT_QUEUE_HPP_
#define _ALT_QUEUE_HPP_

ALT_NAME_SPACE_BEGIN

template<class VALUE,int SIZE>
class TQueue : public TArray<VALUE,SIZE>
{
protected:
	int m_HeadIndex;
public:
	TQueue()
	{
		m_HeadIndex=-1;
	}
	TQueue(const TQueue&Obj)
	{
		m_HeadIndex=-1;
		Resize(Obj.m_Size);
		for(int n=0;n<Obj.m_Count;n++)
			Append(Obj.m_ValueAry[n]);
	}
	void Clear()
	{
		TArray<VALUE,SIZE>::Clear();
		m_HeadIndex=-1;
	}
	VALUE*Append(const VALUE&Value = *(VALUE*)NULL)
	{
		if(m_Size==0)
			return NULL;
		if(m_Count<m_Size)
			m_Count++;
		m_HeadIndex++;
		m_HeadIndex = m_HeadIndex % m_Size;
		if(&Value)
			m_ValueAry[m_HeadIndex] = Value;
		return &m_ValueAry[m_HeadIndex];
	}
	VALUE& operator[](int n)
	{
		return m_ValueAry[(m_HeadIndex-m_Count+n+1+m_Size)%m_Size];
	}
public:
	int	Save(ALTFileStream&Stream)
	{
		int Length;
		Length=Stream.Puts(&m_Size,sizeof(m_Size));
		Length+=Stream.Puts(&m_Count,sizeof(m_Count));
		for(int n=0;n<m_Count;n++)
			Length+=ALTArchiveType::Save(Stream,&m_ValueAry[(m_HeadIndex-m_Count+n+1+m_Size)%m_Size],sizeof(VALUE));
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
		m_HeadIndex = Num?0:-1;
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

