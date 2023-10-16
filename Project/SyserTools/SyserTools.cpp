// SyserTools.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

CAPIMap APIMap;

PCSTR APIPrefixList[]=
{
	"WINSOCK_API_LINKAGE",
	"NTKERNELAPI",
	"WINBASEAPI",
	"NTHALAPI",
	"NTSYSAPI",
	"WINADVAPI",
	"WINGDIAPI",
	"WINUSERAPI",
	"WINMMAPI",
	NULL
};

PCSTR APIMidList[]=
{
	"PASCAL FAR",
	"NTAPI",
	"WINAPI",
	"APIENTRY",
	"WSAAPI",
	"VFWAPI",
	"NTSTATUS\r\nNt",
	"VOID\r\nRtl",
	"NTSTATUS\r\nRtl",
	NULL
};

PCSTR StdcallList[]=
{
	"PASCAL FAR",
	"NTAPI",
	"APIENTRY",
	"WINAPI",
	"WSAAPI",
	NULL
};

PCSTR FastcallList[]=
{
	"FASTCALL",
	NULL
};

PCSTR InlineList[]=
{
	"__inline",
	"INLINE",
	NULL
};

int	APIPrefixLength[32];
int APIMidLength[32];
int	StdcallLength[32];
int	FastcallLength[32];
int InlineLength[32];

bool IsValName(char Str)
{
	if((Str>='0'&&Str<='9')||(Str>='a'&&Str<='z')||(Str>='A'&&Str<='Z'))
		return true;
	if(Str=='_')
		return true;
	return false;
}

bool IsIgnoreChar(char Str)
{
	return TStrChr("\r\n",Str)!=NULL;
}

bool CutAPIDefStr(PSTR pStr,PCSTR*pList,int*pLength)
{
	bool bCutted;
	int n=0;
	bCutted=false;
	while(pList[n])
	{
		if(_GET_DWORD(pStr)==_GET_DWORD(pList[n]) && TStrNCmp(pList[n],pStr,pLength[n])==0)
		{
			bCutted = true;
			if(pStr[pLength[n]]==' ')
				TStrCpy(pStr,&pStr[pLength[n]+1]);
			else
				TStrCpy(pStr,&pStr[pLength[n]]);
			n=0;
		}
		else
			n++;
	}
	return bCutted;
}

bool IsAPIDefStr(PSTR pStr,PCSTR*pList,int*pLength)
{
	int n=0;
	while(pList[n])
	{
		if(_GET_DWORD(pStr)==_GET_DWORD(pList[n]))
		{
			if(TStrNCmp(pList[n],pStr,pLength[n])==0)
				return true;
		}
		n++;
	}
	return false;
}

void AnalyzerAPIParam(PSTR szFunc)
{
	CALL_TYPE CallType = TYPE_STDCALL;
	PSTR pStr,pStrEnd;
	pStr=szFunc;
	while(*pStr)
	{
		CutAPIDefStr(pStr,APIPrefixList,APIPrefixLength);
		if(CutAPIDefStr(pStr,StdcallList,StdcallLength))
			CallType = TYPE_STDCALL;
		if(CutAPIDefStr(pStr,FastcallList,FastcallLength))
			CallType = TYPE_FASTCALL;
		if(CutAPIDefStr(pStr,InlineList,InlineLength))
		{
			CallType = TYPE_INLINE;
			return;
		}
		pStr++;
	}
	pStrEnd = TStrChr(szFunc,'(');
	pStr = pStrEnd-1;
	while(IsValName(*pStr))
		pStr--;
	*pStr=0;
	*pStrEnd=0;
	CAPIMap::IT Iter = APIMap.InsertUnique(&pStr[1]);
	if(Iter.IsExist()==false)
		return;
	Iter->Return = szFunc;
	Iter->CallType = CallType;
	pStrEnd++;
	pStr=pStrEnd;
	while(*pStrEnd)
	{
		if(*pStrEnd==','||*pStrEnd==')')
		{
			*pStrEnd=0;
			Iter->ParamList.Append(pStr);
			pStr=&pStrEnd[1];
		}
		pStrEnd++;
	}
	if(Iter->ParamList.Count()==1 && TStrICmp((PCSTR)*Iter->ParamList.Begin(),"VOID")==0)
	{
		Iter->ParamList.Clear();
	}
}

PSTR AnalyzerAPIDefine(PSTR szStart)
{
	int n,Step;
	bool bIsSplitCharExist;
	CHAR szFuncDefine[1024];
	PSTR szCur,pStr;
	szCur = szStart;
	n=0;
	Step=0;
	bIsSplitCharExist = true;
	while(n<sizeof(szFuncDefine))
	{
		if(*szCur==' '||*szCur=='\t')
		{//Ëõ¼õ²ÎÊý¿Õ¸ñ
			if(bIsSplitCharExist==false)
			{
				bIsSplitCharExist = true;
				szFuncDefine[n++]=' ';
			}
			do
			{
				szCur++;
			}while(*szCur==' '||*szCur=='\t');
		}
		if(IsValName(*szCur))
		{
			bIsSplitCharExist = false;
			szFuncDefine[n++]=*szCur++;
		}
		else
		{
			if(IsIgnoreChar(*szCur))
			{
				if(bIsSplitCharExist==false)
				{
					szFuncDefine[n++]=' ';
					bIsSplitCharExist=true;
				}
				szCur++;
				continue;
			}
			switch(*szCur)
			{
			case '(':
				if(Step==0)
				{
					bIsSplitCharExist=true;
					do
					{
						n--;
					}while(szFuncDefine[n]==' ');
					n++;
					szFuncDefine[n++]=*szCur++;
					Step++;
				}
				else
					return szCur;
				break;
			case ',':
				if(Step==1)
				{
					bIsSplitCharExist=true;
					szFuncDefine[n++]=*szCur++;
				}
				else
					return szCur;
				break;
			case ')':
				if(Step<=1)
				{
					pStr = &szFuncDefine[n];
					do
					{
						pStr--;
					}while(*pStr==' ');
					*pStr++;
					*pStr++=')';*pStr=0;
					szCur++;
					AnalyzerAPIParam(szFuncDefine);
					return szCur;
				}
				else
					return szCur;
				break;
			case '*':
				szFuncDefine[n++]=*szCur++;
				if(IsValName(*szCur))
				{
					bIsSplitCharExist = true;
					szFuncDefine[n++]=' ';
				}
				break;
			default:
				szCur++;
				return szCur;
			}
		}
	}
	return &szStart[sizeof(szFuncDefine)];
}


void InsertAPIDefine(PCSTR FileName)
{
	CHAR*szBuffer,*szEndBuffer,*pCurStr,*pStr,*pLastStr;
	int Length;
	CImageFile File;
	if(File.Open(FileName)==false)
		return;
	Length = File.m_FileSize;
	szBuffer = new CHAR[Length+1];
	szEndBuffer = &szBuffer[Length];
	File.ReadFile(szBuffer,Length);
	*szEndBuffer=0;
	pCurStr = szBuffer;
	while(pCurStr && pCurStr<szEndBuffer)
	{
		if(IsAPIDefStr(pCurStr,APIPrefixList,APIPrefixLength))
			pCurStr=AnalyzerAPIDefine(pCurStr);
		if(IsAPIDefStr(pCurStr,APIMidList,APIMidLength))
		{
			pStr=pCurStr;
			pLastStr = NULL;
			while(true)
			{
				if(IsValName(*pCurStr)||*pCurStr=='*'||*pCurStr==' '||*pCurStr=='\t')
				{
					pStr = pCurStr;
					pCurStr--;
				}
				else if(IsIgnoreChar(*pCurStr))
				{
					pLastStr = pCurStr;
					pCurStr--;
				}
				else
				{
					if(pLastStr)
						pStr = pLastStr;
					break;
				}
			}
			if(pLastStr)
				pCurStr=AnalyzerAPIDefine(pStr);
			else
				pCurStr=TStrChr(pCurStr,'\n');
		}
		else 
			pCurStr++;
	}
	delete szBuffer;
	File.Close();
}

int SaveLib(PCSTR LibName)
{
	int LibSize;
	CALTFileStream FileStream;
	FileStream.Create(LibName);
	LibSize = APIMap.Save(FileStream);
	FileStream.Close();
	return LibSize;
}

XSCAN_RES ScanCallBack(CFileIO*pFileIO,PCSTR FileName,ULSIZE FileSize,void*CBParam)
{
	InsertAPIDefine(FileName);
	return XSCAN_RES_CONTINUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int Length,n,LibSize;
	CHAR szBuffer[1024];

	for(n=0;APIPrefixList[n];n++)
		APIPrefixLength[n]=TStrLen(APIPrefixList[n]);
	for(n=0;APIMidList[n];n++)
		APIMidLength[n]=TStrLen(APIMidList[n]);
	for(n=0;StdcallList[n];n++)
		StdcallLength[n]=TStrLen(StdcallList[n]);
	for(n=0;FastcallList[n];n++)
		FastcallLength[n]=TStrLen(FastcallList[n]);
	for(n=0;InlineList[n];n++)
		InlineLength[n]=TStrLen(InlineList[n]);

	gpFileIO->XScan("APILib\\*.h",ScanCallBack,0,false);
	LibSize = 0;
	if(APIMap.Count())
		LibSize = SaveLib("APIDef.lib");
	CALTFileStream FileStream;

	if(FileStream.Create("API.TXT")==false)
		return 0;
	for(CAPIMap::IT APIIter = APIMap.Begin();APIIter != APIMap.End();APIIter++)
	{
		//printf("%s\n",(PCSTR)APIIter.Key());
		Length =TStrCpy(szBuffer,(PCSTR)APIIter->Return);
		Length+=TStrCpy(&szBuffer[Length]," ");
		Length+=TStrCpy(&szBuffer[Length],(PCSTR)APIIter.Key());
		Length+=TStrCpy(&szBuffer[Length],"(");
		for(TList<CStrA>::IT Iter=APIIter->ParamList.Begin();Iter!=APIIter->ParamList.End();Iter++)
		{
			Length+=TStrCpy(&szBuffer[Length],(PCSTR)*Iter);
			if(Iter!=APIIter->ParamList.Last())
				Length+=TStrCpy(&szBuffer[Length],",");
		}
		Length+=TStrCpy(&szBuffer[Length],")");
		Length+=TStrCpy(&szBuffer[Length],"\r\n");
		FileStream.Puts(szBuffer,Length);
	}
	FileStream.Close();

	printf("%d API(s)\n",APIMap.Count());

	FileStream.Open("APIDef.lib");
	Length = APIMap.Load(FileStream);
	FileStream.Close();
	int MaxParamCount=0,MaxStrLen=0;

	for(CAPIMap::IT APIIter = APIMap.Begin();APIIter.IsExist();APIIter++)
	{
		TStrCpy(szBuffer,(PCSTR)APIIter.Key());
		if(APIIter->ParamList.Count()>MaxParamCount)
		{
			MaxParamCount = APIIter->ParamList.Count();
		}
		for(TList<CStrA>::IT ParamIter=APIIter->ParamList.Begin();ParamIter!=APIIter->ParamList.End();ParamIter++)
		{
			if(ParamIter->Length()>MaxStrLen)
				MaxStrLen = ParamIter->Length();
			TStrCpy(szBuffer,(PCSTR)*ParamIter);	
		}
	}
	printf("Save Length = %d , Load Length = %d\n",LibSize,Length);
	return 0;
}