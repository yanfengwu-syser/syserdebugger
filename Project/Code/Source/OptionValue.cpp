#include "StdAfx.h"
#include "OptionValue.h"


COptionValue::COptionValue()
{

}

COptionValue::~COptionValue()
{

}

void COptionValue::RegisterValueAry(STRegOptVal*pValAry)
{
	while(pValAry->szName)
	{
		switch(pValAry->Type)
		{
		case STOptVal::STR_VAL:
			InsertStrValue(pValAry->szName,(WCHAR*)pValAry->pValue,pValAry->Length);
			break;
		case STOptVal::INT_VAL:
			InsertIntValue(pValAry->szName,(int*)pValAry->pValue);
			break;
		case STOptVal::UINT_VAL:
			InsertUintValue(pValAry->szName,(UINT*)pValAry->pValue);
			break;
		case STOptVal::FLOAT_VAL:
			InsertFloatValue(pValAry->szName,(float*)pValAry->pValue);
			break;
		}
		pValAry++;
	}
}

//Unicode
bool COptionValue::InsertStrValue(PCWSTR szName,WCHAR*pValue,int Length)
{
	COptValMap::IT Iter = m_OptValMap.InsertUnique(szName);
	if(Iter==m_OptValMap.End())
		return false;
	Iter->Type = STOptVal::STR_VAL;
	Iter->pStrVal = pValue;
	Iter->Length = Length;
	return true;
}

bool COptionValue::InsertIntValue(PCWSTR szName,int*pValue)
{
	COptValMap::IT Iter = m_OptValMap.InsertUnique(szName);
	if(Iter==m_OptValMap.End())
		return false;
	Iter->Type = STOptVal::INT_VAL;
	Iter->pIntVal = pValue;
	Iter->Length = sizeof(int);
	return true;
}

bool COptionValue::InsertUintValue(PCWSTR szName,UINT*pValue)
{
	COptValMap::IT Iter = m_OptValMap.InsertUnique(szName);
	if(Iter==m_OptValMap.End())
		return false;
	Iter->Type = STOptVal::UINT_VAL;
	Iter->pUintVal = pValue;
	Iter->Length = sizeof(UINT);
	return true;
}

bool COptionValue::InsertFloatValue(PCWSTR szName,float*pValue)
{
	COptValMap::IT Iter = m_OptValMap.InsertUnique(szName);
	if(Iter==m_OptValMap.End())
		return false;
	Iter->Type = STOptVal::FLOAT_VAL;
	Iter->pFloatVal = pValue;
	Iter->Length = sizeof(float);
	return true;
}

bool COptionValue::RemoveValue(PCWSTR szName)
{
	return m_OptValMap.Remove(szName)!=0;
}


STOptVal::TYPE COptionValue::GetValue(PCWSTR szName,void**ppValue,int*pLength)
{
	COptValMap::IT Iter = m_OptValMap.Find(szName);
	if(Iter==m_OptValMap.End())
		return STOptVal::NULL_VAL;
	*ppValue = Iter->pValue;
	if(pLength)
		*pLength = Iter->Length;
	return Iter->Type;
}

WCHAR*COptionValue::GetStrValue(PCWSTR szName,int*pLength)
{
	COptValMap::IT Iter = m_OptValMap.Find(szName);
	if(Iter==m_OptValMap.End())
		return NULL;
	if(Iter->Type != STOptVal::STR_VAL)
		return NULL;
	if(pLength)
		*pLength = Iter->Length;
	return Iter->pStrVal;
}

int*COptionValue::GetIntValue(PCWSTR szName)
{
	COptValMap::IT Iter = m_OptValMap.Find(szName);
	if(Iter==m_OptValMap.End())
		return NULL;
	if(Iter->Type != STOptVal::INT_VAL)
		return NULL;
	return Iter->pIntVal;
}

UINT*COptionValue::GetUintValue(PCWSTR szName)
{
	COptValMap::IT Iter = m_OptValMap.Find(szName);
	if(Iter==m_OptValMap.End())
		return NULL;
	if(Iter->Type != STOptVal::UINT_VAL)
		return NULL;
	return Iter->pUintVal;
}

float*COptionValue::GetFloatValue(PCWSTR szName)
{
	COptValMap::IT Iter = m_OptValMap.Find(szName);
	if(Iter==m_OptValMap.End())
		return NULL;
	if(Iter->Type != STOptVal::FLOAT_VAL)
		return NULL;
	return Iter->pFloatVal;
}

//Ansi
bool COptionValue::InsertStrValue(PCSTR szName,WCHAR*pValue,int Length)
{
	WCHAR wszName[MAX_LONG_NAME_LEN];
	AnsiToUnicode(szName,wszName,MAX_LONG_NAME_LEN);
	return InsertStrValue(wszName,pValue,Length);
}

bool COptionValue::InsertIntValue(PCSTR szName,int*pValue)
{
	WCHAR wszName[MAX_LONG_NAME_LEN];
	AnsiToUnicode(szName,wszName,MAX_LONG_NAME_LEN);
	return InsertIntValue(wszName,pValue);
}

bool COptionValue::InsertUintValue(PCSTR szName,UINT*pValue)
{
	WCHAR wszName[MAX_LONG_NAME_LEN];
	AnsiToUnicode(szName,wszName,MAX_LONG_NAME_LEN);
	return InsertUintValue(wszName,pValue);
}

bool COptionValue::InsertFloatValue(PCSTR szName,float*pValue)
{
	WCHAR wszName[MAX_LONG_NAME_LEN];
	AnsiToUnicode(szName,wszName,MAX_LONG_NAME_LEN);
	return InsertFloatValue(wszName,pValue);
}

bool COptionValue::RemoveValue(PCSTR szName)
{
	WCHAR wszName[MAX_LONG_NAME_LEN];
	AnsiToUnicode(szName,wszName,MAX_LONG_NAME_LEN);
	return RemoveValue(wszName);
}
