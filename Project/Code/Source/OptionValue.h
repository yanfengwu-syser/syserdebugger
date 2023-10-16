#ifndef _OPTION_VALUE_H_
#define _OPTION_VALUE_H_

struct STOptVal
{
	enum TYPE{NULL_VAL,STR_VAL,INT_VAL,UINT_VAL,FLOAT_VAL};
	TYPE Type;
	union
	{
		int*pIntVal;
		UINT*pUintVal;
		WCHAR*pStrVal;
		float*pFloatVal;
		void*pValue;
	};
	int Length;
};

struct STRegOptVal
{
	PCWSTR szName;
	STOptVal::TYPE Type;
	void*pValue;
	int Length;
};

typedef TMap<CIStrW,STOptVal>	COptValMap;

class COptionValue
{
public:
	COptionValue();
	~COptionValue();
public://Unicode
	//Insert
	void RegisterValueAry(STRegOptVal*pValAry);
	bool InsertStrValue(PCWSTR szName,WCHAR*pValue,int Length);
	bool InsertIntValue(PCWSTR szName,int*pValue);
	bool InsertUintValue(PCWSTR szName,UINT*pValue);
	bool InsertFloatValue(PCWSTR szName,float*pValue);
	//Remove
	bool RemoveValue(PCWSTR szName);
	//GetValue
	STOptVal::TYPE GetValue(PCWSTR szName,void**ppValue,int*pLength);
	WCHAR*GetStrValue(PCWSTR szName,int*pLength);
	int*GetIntValue(PCWSTR szName);
	UINT*GetUintValue(PCWSTR szName);
	float*GetFloatValue(PCWSTR szName);
public://Ansi
	//Insert
	bool InsertStrValue(PCSTR szName,WCHAR*pValue,int Length);
	bool InsertIntValue(PCSTR szName,int*pValue);
	bool InsertUintValue(PCSTR szName,UINT*pValue);
	bool InsertFloatValue(PCSTR szName,float*pValue);
	//Remove
	bool RemoveValue(PCSTR szName);
public:
	COptValMap	m_OptValMap;
};

#endif
