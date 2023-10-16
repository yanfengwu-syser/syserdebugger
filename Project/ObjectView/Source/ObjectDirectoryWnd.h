#ifndef _OBJECTDIRECTORYWND_H_
#define _OBJECTDIRECTORYWND_H_
#ifdef CODE_OS_NT_DRV 
#include "ObjectDirectory.h"
#endif
enum
{
	CHILD_WND_ID_OBJECTDIRECTORYTRE=WISP_ID_USER_START+600,
	CHILD_WND_ID_OBJECTLIST,
};

class CObjectDirectoryWnd:public CWispSplitWnd
{
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnCmdObjectDirectory)
	DECLARE_WISP_MSG_CMD(OnCmdObjectList)
	CWispList m_ObjectDirectoryTree;
	CWispList m_ObjectList;
	bool UpdateContext();
	bool InitContext();
	bool InitContext(DWORD ObjectHandle,HANDLE hItem);
	bool InitContext(HANDLE hItem);
	bool ObjectList(HANDLE hItem);
};

#endif

