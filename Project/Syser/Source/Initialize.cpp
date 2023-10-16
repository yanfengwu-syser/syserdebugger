#include "stdafx.h"
#include "Initialize.h"


void InitOSVersionInfo()
{
	gOSCheckedBuild=PsGetVersion(&gOSMajorVersion,&gOSMinorVersion,&gOSBuildNumber,NULL);
}