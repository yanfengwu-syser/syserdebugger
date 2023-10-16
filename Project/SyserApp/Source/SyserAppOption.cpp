#include "StdAfx.h"
#include "SyserAppOption.h"

int	SyserAppOptionRef = 0;
int SyserAppBootTypeRef = 0;
int	iBootType;
int	OrgiBootType = 3;

SYSER_APP_OPTION OrgSyserAppOption = 
{
	0,//CRCCode
	1,//iSystemTray
	1,//iAutoStart
	2,//iAutoStop
	0,//iTopMost
	300,//iHistroyLines;
};

SYSER_APP_OPTION SyserAppOption;

STRegOptVal SyserAppOptVal[]=
{
	{WSTR("iSystemTray"),			STOptVal::INT_VAL,	&SyserAppOption.iSystemTray},
	{WSTR("iAutoStart"),			STOptVal::INT_VAL,	&SyserAppOption.iAutoStart},
	{WSTR("iAutoStop"),				STOptVal::INT_VAL,	&SyserAppOption.iAutoStop},
	{WSTR("iTopMost"),				STOptVal::INT_VAL,	&SyserAppOption.iTopMost},
	{WSTR("iHistroyLines"),			STOptVal::INT_VAL,	&SyserAppOption.iHistroyLines},
	{NULL}
};

