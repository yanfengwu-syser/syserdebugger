///////////////////////////////////////////////////////////////////////////////
//Stach
//Coded by Finaldoom
//Õ»
//×÷Õß£º³Â¿¡ºÀ
///////////////////////////////////////////////////////////////////////////////
#ifndef _ALT_STACK_HPP_
#define _ALT_STACK_HPP_

ALT_NAME_SPACE_BEGIN

template<class VALUE,int Size>
class TStack : public TQueue<VALUE,Size>
{
public:
	void Push(const VALUE&Value)
	{
		Append(Value);
	}
	bool Pop(VALUE&Value)
	{
		int Index;
		if(m_Count<=0)
			return false;
		Index=(m_HeadIndex+m_Size)%m_Size;
		m_HeadIndex--;
		m_HeadIndex = m_HeadIndex % m_Size;
		m_Count--;
		Value = m_ValueAry[Index];
		return true;
	}
	VALUE& operator[](int n)
	{
		return m_ValueAry[(m_HeadIndex+m_Size-n)%m_Size];
	}
};

ALT_NAME_SPACE_END

#endif

