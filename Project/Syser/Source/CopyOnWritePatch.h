#ifndef _COPY_ON_WRITE_PATCH_H_
#define _COPY_ON_WRITE_PATCH_H_

struct ST_COPY_ON_WRITE_OS_INFO
{
	BYTE*	CodeFeature;
	int		CodeFeatureLen;
	bool	bIsFastCall;
	ULONG	MajorVersion;
	ULONG	MinorVersion;
};

void PatchMiCopyOnWrite();

#endif
