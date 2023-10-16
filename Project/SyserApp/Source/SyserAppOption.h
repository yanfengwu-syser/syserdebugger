#ifndef _SYSER_APP_OPTION_H_
#define _SYSER_APP_OPTION_H_

struct SYSER_APP_OPTION
{
	DWORD	CRCCode;
	int		iSystemTray;
	int		iAutoStart;
	int		iAutoStop;
	int		iTopMost;
	int		iHistroyLines;
};

extern SYSER_APP_OPTION OrgSyserAppOption;
extern SYSER_APP_OPTION SyserAppOption;
extern STRegOptVal SyserAppOptVal[];

#endif

