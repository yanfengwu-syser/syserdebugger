#ifndef _ALT_VECTOR_H_
#define _ALT_VECTOR_H_

#include "ALTBase.hpp"

ALT_NAME_SPACE_BEGIN

template<class VALUE,int InitSize = 0,class ALTArchiveType = ALTEmptyArchive> //	ALTArchive>
class TVector : public ALTObj<VALUE>
{
public:
	int		m_Size;
	int		m_Count;
	VALUE**	m_ValueAry;			
public:
	TVector()
	{
		m_ValueAry = NULL;
		m_Count = m_Size = 0;
		Resize(InitSize);
	}
	~TVector()
	{
		Clear();
	}
public:
	void Resize(int NewSize)
	{
		VALUE**	NewVauleArray;
		if(NewSize==m_Size)
			return;
		NewVauleArray = (VALUE**)ConstructPtrArray(NewSize);
		for(int n=0;n<NewSize;n++)
			NewVauleArray[n]=NULL;
		if(m_Count>NewSize)
			m_Count=NewSize;
		if(m_ValueAry)
		{
			for(int n=0;n<m_Count;n++)
				NewVauleArray[n] = m_ValueAry[n];
			DestructPtrArray(m_ValueAry);			
		}
		m_ValueAry = NewVauleArray;
		m_Size = NewSize;
	}
	void Clear()
	{
		if(m_ValueAry)
		{
			for(int n=0;n<m_Count;n++)
			{
				Destruct(m_ValueAry[n]);
			}
			DestructPtrArray(m_ValueAry);
			m_ValueAry = NULL;
		}
		m_Size = m_Count = 0;		
	}
	VALUE*Append(const VALUE&Value = *(VALUE*)NULL)
	{
		if(m_Count+1>=m_Size)
			Resize(m_Size*2);
		m_ValueAry[m_Count]=Construct();
		if(&Value)
			*m_ValueAry[m_Count]=Value;
		m_Count++;
		return m_ValueAry[m_Count-1];
	}
	void Remove()
	{
		if(m_Count<=0)
			return;
		m_Count--;
		Destruct(m_ValueAry[m_Count]);
		m_ValueAry[m_Count]=NULL;
	}
	inline VALUE& operator[](int n)const
	{
		return *m_ValueAry[n];
	}
	inline int Size(){return m_Size;}
	inline int Count(){return m_Count;}
public:
	int	Save(ALTFileStream&Stream)
	{
		int Length;
		Length=Stream.Puts(&m_Size,sizeof(m_Size));
		Length+=Stream.Puts(&m_Count,sizeof(m_Count));
		for(int n=0;n<m_Count;n++)
			Length+=ALTArchiveType::Save(Stream,m_ValueAry[n],sizeof(VALUE));
		return Length;
	}
	int	Load(ALTFileStream&Stream)
	{
		int Length,Num;
		Clear();
		Length=Stream.Gets(&Num,sizeof(Num));
		Resize(Num);
		Length+=Stream.Gets(&Num,sizeof(Num));
		for(int n=0;n<Num;n++)
			Length+=ALTArchiveType::Load(Stream,Append(),sizeof(VALUE));
		return Length;
	}
	static	int	Save(ALTFileStream&Stream,TVector*Obj,int m_Size){	return Obj->Save(Stream); }
	static	int	Load(ALTFileStream&Stream,TVector*Obj,int m_Size){	return Obj->Load(Stream); }
};


ALT_NAME_SPACE_END

#endif
