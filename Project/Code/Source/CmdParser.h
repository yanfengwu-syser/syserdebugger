#ifndef _CMD_PARSER_H_
#define _CMD_PARSER_H_

#include "TStrMem.h"

NAME_SPACE_BEGIN

typedef WCHAR CMD_CHAR;
typedef int(*CMDPROC)(int argc,CMD_CHAR*argv[],const CMD_CHAR* szCommandLine,void*pUserData);
typedef TString<CMD_CHAR,true>			CCmdString;

struct COMMAND_ENTRY
{
	const CMD_CHAR*	pComment;
	const CMD_CHAR*	pUsage;
	CMDPROC		pCmdProc;
	void*		pUserData;
};

typedef TMap<CCmdString,COMMAND_ENTRY>	CCmdMap;
#define	MAX_CHARS_PER_LINE				256
#define	MAX_PARAM_PER_LINE				32

class CCmdParser
{
public:
	CCmdParser(void);
	 ~CCmdParser(void);
public:
	virtual void PrintString(const CMD_CHAR* pString){};
public:
	CCmdMap		m_CmdMap;
public:
	virtual	void	Reset();
	virtual	bool	InsertCmd(const CMD_CHAR*szCmd,CMDPROC pCmdProc,void*pUserData,const CMD_CHAR*pComment,const CMD_CHAR*pUsage);
	virtual	void	RemoveCmd(const CMD_CHAR*szCmd);
	int		ParseCmd(CMD_CHAR*szCmd,CMD_CHAR*pszCmdParam[]);
	bool	RunCmd(const CMD_CHAR*szCmd,int*pResult = NULL);
	void	RunCmdList(const CMD_CHAR*szCmd,CMD_CHAR SplitChar=';');
	bool	CmpCmd(const CMD_CHAR*szCmd1,const CMD_CHAR*szCmd2);
};

NAME_SPACE_END

#endif

