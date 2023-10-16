
#ifndef __ANALYSECOM_H__
#define __ANALYSECOM_H__


#include <OAIdl.h>
#include <OleAuto.h>
#include <list>
#include <map>
#include <string>

using namespace std;
#define _CRT_SECURE_NO_WARNINGS

typedef HRESULT (__stdcall *  DLLREGISTERSERVER)();
typedef HRESULT (__stdcall *  DLLUNREGISTERSERVER)();
typedef struct _COM_CLASS
{
	int			index;
	IUnknown* pIunknow;
}COM_CLASS,*PCOM_CLASS;

typedef map<string,COM_CLASS> INTERFACE_MAP;
typedef map<string,DWORD> COMSYMBOL_MAP;
int GetComSymbols(char* dllname,COMSYMBOL_MAP& symmap);

#endif //__ANALYSECOM_H__
