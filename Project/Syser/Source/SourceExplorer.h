#ifndef _SOURCE_EXPLORER_H_
#define _SOURCE_EXPLORER_H_

class CSourceExplorer : public CWispWnd
{
public:
	CSourceExplorer();
	~CSourceExplorer();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
};


#endif
