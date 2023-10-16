// AnalyseCom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// ddd1.cpp : Defines the entry point for the console application.
//
#include "AnalyseCom.h"

//#include "stdafx.h"
//#include <OAIdl.h>
//#include <OleAuto.h>
//#include <list>
//#include <map>
//#include <string>
//#include <objbase.h>
//using namespace std;
//#define _CRT_SECURE_NO_WARNINGS
//
//typedef HRESULT (__stdcall *  DLLREGISTERSERVER)();
//typedef HRESULT (__stdcall *  DLLUNREGISTERSERVER)();
//typedef struct _COM_CLASS
//{
//	int			index;
//	IUnknown* pIunknow;
//}COM_CLASS,*PCOM_CLASS;
//
//typedef map<string,COM_CLASS> INTERFACE_MAP;
//typedef map<string,DWORD> COMSYMBOL_MAP;
//
//
//int Usage(_TCHAR* name)
//{
//	int j=-1;
//	for(int i=0;name[i];i++)
//	{
//		if(name[i]=='\\')
//			j=i;
//	}
//
//	fprintf(stderr,"Websense com symbol analyse version 1.0.0\n");
//	fprintf(stderr,"(C) Websense Corporation, 2002-2009\n\n");
//	fprintf(stderr,"Usages: %S comfilename\n",name+j+1);
//	return 0;
//}
//int GetComSymbols(char* dllname,COMSYMBOL_MAP& symmap);
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}
int GetComSymbols(char* dllname,COMSYMBOL_MAP& symmap)
{
	char* libname;
	char funcname[0x200];
	ITypeLib * pLib;
	HRESULT result;
	char claid[500];
	TYPEATTR* pTypeAddr;
	ITypeInfo* pTypeInfo;
	WCHAR oleName[MAX_PATH];
	DLLREGISTERSERVER fpDllRegisterServer=NULL;
	DLLUNREGISTERSERVER fpDllUnregisterServer=NULL;
	HMODULE hModule=NULL;
	FUNCDESC* FuncDesc;
	LPOLESTR wClsid;
	BSTR FuncName;
	IUnknown* IUnknow1;	
	COM_CLASS ComClass;
	INTERFACE_MAP::iterator BeginIT,EndIT;
	INTERFACE_MAP InterfaceMap;
	sprintf(claid,"%s",dllname);
	libname=claid;	
	
	hModule = LoadLibrary(libname);;

	if(hModule)
	{
		fpDllRegisterServer =(DLLREGISTERSERVER) GetProcAddress(hModule,"DllRegisterServer");
		fpDllUnregisterServer =(DLLUNREGISTERSERVER) GetProcAddress(hModule,"DllUnregisterServer");
	}
	result = LoadTypeLibEx(oleName,REGKIND_DEFAULT,&pLib);	
	if(result!=0)
		return 0;
	CoInitialize(NULL);
	{	
		UINT count=0;
		UINT i;
		count = pLib->GetTypeInfoCount();
		for(i=0;i<count;i++)
		{
			result = pLib->GetTypeInfo(i,&pTypeInfo);
			if(result==0)
			{

				if(pTypeInfo->GetTypeAttr(&pTypeAddr)>=0)
				{	
					if(pTypeAddr->typekind==TKIND_COCLASS)
					{						
						StringFromCLSID(pTypeAddr->guid,&wClsid);
						result=0;
						sprintf(claid,"%S",wClsid);
						result = CoCreateInstance(pTypeAddr->guid,NULL,    CLSCTX_INPROC_SERVER |CLSCTX_INPROC_HANDLER|CLSCTX_LOCAL_SERVER,  IID_IUnknown,(LPVOID*)&IUnknow1);
						if(result == REGDB_E_CLASSNOTREG && fpDllRegisterServer)
						{
							fpDllRegisterServer();
							result = CoCreateInstance(pTypeAddr->guid,NULL,    CLSCTX_INPROC_SERVER |CLSCTX_INPROC_HANDLER|CLSCTX_LOCAL_SERVER, IID_IUnknown,(LPVOID*)&IUnknow1);
						}

						if(result==0 && IUnknow1)
						{
							ComClass.index=i;
							ComClass.pIunknow=IUnknow1;
							InterfaceMap.insert(INTERFACE_MAP::value_type(claid,ComClass));
						}																						
					}
					pTypeInfo->ReleaseTypeAttr(pTypeAddr);		
				}
				pTypeInfo->Release();
			}

		}

		for(i=0;i<count;i++)
		{
			result = pLib->GetTypeInfo(i,&pTypeInfo);
			if(result==0)
			{				
				if(pTypeInfo->GetTypeAttr(&pTypeAddr)>=0)
				{

					if(pTypeAddr->cFuncs)
					{
						StringFromCLSID(pTypeAddr->guid,&wClsid);
						result=0;
						sprintf(claid,"%S",wClsid);
						printf("%s\n",claid);
						for(WORD j=0;j<pTypeAddr->cFuncs;j++)
						{
							if(pTypeInfo->GetFuncDesc(j,&FuncDesc)>=0)
							{								
								if(pTypeInfo->GetDocumentation(FuncDesc->memid,&FuncName,NULL,NULL,NULL)>=0)
								{
									sprintf(funcname,"%S",FuncName);									
									count++;
									SysFreeString(FuncName);
									BeginIT=InterfaceMap.begin();
									EndIT=InterfaceMap.end();
									for(;BeginIT!=EndIT;BeginIT++)
									{
										PVOID pObject;
										result = BeginIT->second.pIunknow->QueryInterface(pTypeAddr->guid,&pObject);
										if(result>=0)
										{
											DWORD **pvt = (DWORD**)pObject;
											DWORD * pfvt=pvt[0];											
											DWORD offset=pfvt[FuncDesc->oVft/4];
											offset-=*(DWORD*)&hModule;										
											symmap.insert(COMSYMBOL_MAP::value_type(funcname,offset));
											break;									
										}										
									}
									
								}
								pTypeInfo->ReleaseFuncDesc(FuncDesc);
							}
						}						
					}
					//if(pTypeAddr->cVars)
					//{
					//	for(WORD m=0;m<pTypeAddr->cVars;m++)
					//	{
					//		
					//		if(pTypeInfo->GetVarDesc(m,&VarDesc)>=0)
					//		{
					//			if(pTypeInfo->GetDocumentation(VarDesc->memid,&VarName,NULL,NULL,NULL)>=0)
					//			{
					//				printf("var %ws   %d  \n",VarName,VarDesc->varkind);
					//			}
					//		}
					//	}
					//}
					//if(pTypeAddr->cImplTypes)
					//{
					//	HREFTYPE hRefType;
					//	for(WORD n=0;n<pTypeAddr->cImplTypes;n++)
					//	{
					//		if(pTypeInfo->GetRefTypeOfImplType(n,&hRefType)>=0)
					//		{
					//			printf("[%d] GetRefTypeOfImplType %x\n",n,hRefType);
					//		}
					//	}
					//}
				}
				pTypeInfo->ReleaseTypeAttr(pTypeAddr);
				pTypeInfo->Release();
			}
		}
	}

	pLib->Release();
	FreeLibrary(hModule);
	BeginIT=InterfaceMap.begin();
	EndIT=InterfaceMap.end();
	for(;BeginIT!=EndIT;BeginIT++)
	{
		BeginIT->second.pIunknow->Release();
	}
	InterfaceMap.clear();
	CoUninitialize();
	return symmap.size();
}



