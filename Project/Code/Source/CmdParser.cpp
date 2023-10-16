#include "StdAfx.h"
#include "CmdParser.h"

NAME_SPACE_BEGIN

CCmdParser::CCmdParser(void)
{
}

CCmdParser::~CCmdParser(void)
{
}

bool CCmdParser::InsertCmd(const CMD_CHAR*szCmd,CMDPROC pCmdProc,void*pUserData,const CMD_CHAR*pComment,const CMD_CHAR*pUsage)
{
	CMD_CHAR szCmdBuff[256];
	CCmdMap::IT Iter;
	TStrCpy(szCmdBuff,szCmd);
	TStrLwr(szCmdBuff);
	Iter = m_CmdMap.InsertUnique(szCmdBuff);
	if(Iter==m_CmdMap.End())
		return false;
	Iter->pCmdProc = pCmdProc;
	Iter->pComment = pComment;
	Iter->pUserData = pUserData;
	Iter->pUsage = pUsage;
	return true;
}

void CCmdParser::RemoveCmd(const CMD_CHAR*szCmd)
{
	CCmdString Str(szCmd);
	Str.MakeLower();
	m_CmdMap.Remove(Str);
}

void CCmdParser::Reset()
{
	m_CmdMap.Clear();
}

int CCmdParser::ParseCmd(CMD_CHAR*szCmd,CMD_CHAR*pszCmdParam[])
{
	CMD_CHAR*pStr;
	int Length,ParamCount;
	Length = TStrLen(szCmd);
	while(Length)
	{
		Length--;
		if(szCmd[Length]=='\n')
			szCmd[Length]=0;
	}
	ParamCount=1;
	pStr=szCmd;
	pszCmdParam[0] = pStr;
	while(*pStr)
	{
		pStr = TStrChr(pStr,' ');
		if(pStr==NULL)
			break;
		while(*pStr==' ')
		{
			*pStr=0;
			pStr++;
		}
		if(*pStr)
		{
			pszCmdParam[ParamCount]=pStr;
			ParamCount++;
		}
	}
	return ParamCount;
}

bool CCmdParser::RunCmd(const CMD_CHAR*szCmd,int*pResult)
{
	CMD_CHAR CmdStr[MAX_CHARS_PER_LINE],*CmdParam[MAX_PARAM_PER_LINE];
	int Result,Length,ParamCount;
	while(*szCmd==' '||*szCmd=='\t')
		szCmd++;
	Length = TStrCpyLimit(CmdStr,szCmd,MAX_CHARS_PER_LINE);
	if(Length==0)
		return false;
	ParamCount = ParseCmd(CmdStr,CmdParam);
	CCmdMap::IT Iter=m_CmdMap.Find(CmdStr);
	if(Iter!=m_CmdMap.End())
	{
		Result = Iter->pCmdProc(ParamCount,CmdParam,szCmd,Iter->pUserData);
		if(pResult)
			*pResult = Result;
		return true;
	}
	return false;
}

void CCmdParser::RunCmdList(const CMD_CHAR*szCmd,CMD_CHAR SplitChar)
{
	const CMD_CHAR*pBegin,*pEnd;
	CMD_CHAR szCurCmd[512];
	pBegin = szCmd;
	while(pBegin && *pBegin)
	{
		while(*pBegin==SplitChar)
			pBegin++;
		pEnd = TStrChr(pBegin,SplitChar);
		if(pEnd)
		{
			TStrCpyLimit(szCurCmd,pBegin,MIN((int)(pEnd-pBegin),512));
			pBegin = pEnd;
		}
		else
		{
			TStrCpyLimit(szCurCmd,pBegin,512);
			pBegin = NULL;
		}		
		RunCmd(szCurCmd);
	}
}

bool CCmdParser::CmpCmd(const CMD_CHAR*szCmd1,const CMD_CHAR*szCmd2)
{
	CMD_CHAR CmdStr1[MAX_CHARS_PER_LINE],*CmdParam1[MAX_PARAM_PER_LINE];
	CMD_CHAR CmdStr2[MAX_CHARS_PER_LINE],*CmdParam2[MAX_PARAM_PER_LINE];
	int ParamCount1,ParamCount2;
	TStrCpyLimit(CmdStr1,szCmd1,MAX_CHARS_PER_LINE);
	TStrCpyLimit(CmdStr2,szCmd2,MAX_CHARS_PER_LINE);
	ParamCount1 = ParseCmd(CmdStr1,CmdParam1);
	ParamCount2 = ParseCmd(CmdStr2,CmdParam2);
	if(ParamCount1!=ParamCount2)
		return false;
	for(int n=0;n<ParamCount1;n++)
	{
		if(TStrCmp(CmdParam1[1],CmdParam1[2]))
			return false;
	}
	return true;
}

NAME_SPACE_END

