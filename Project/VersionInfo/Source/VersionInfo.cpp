// VersionInfo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VersionInfo.h"
int main(int argc, char* argv[])
{
	if(argc==1)
	{
		printf("%s [--MAJOR | --MINOR | --BUILDNUMBER | --BUILDDATE]\n");
		return 0;
	}
	if(argc==2)
	{
		if(TStrICmp(argv[1],"--MAJOR")==0)
			printf("%d",VER_PRODUCTMAJORVERSION);
		else if(TStrICmp(argv[1],"--MINOR")==0)
			printf("%d",VER_PRODUCTMINORVERSION);
		else if(TStrICmp(argv[1],"--BUILDNUMBER")==0)
			printf("%d",VER_PRODUCTBUILD);
		else if(TStrICmp(argv[1],"--BUILDDATE")==0)
			printf("%s",__DATE__);
		else
			printf("0");
		return 0;
	}
	return -1;
}

