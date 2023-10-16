#ifndef _MAIN_FRAME_H_
#define _MAIN_FRAME_H_

#include "ObjectDirectoryWnd.h"

class CMainFrame : public CWispWnd
{
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnSize);
public:
   CObjectDirectoryWnd m_ObjectWnd;
   CWispSplitWnd m_SplitWnd;
};

#endif
