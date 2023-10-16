#ifndef _PROCESS_LIST_H_
#define _PROCESS_LIST_H_

#include "DbgProcess.h" 

class CProcessList : public CWispList
{
public:
	CProcessList();
	~CProcessList();
	void	Popup();
	void	UpdateContext();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG(OnKeyEvent)
#ifdef CODE_OS_WIN
	HANDLE	m_hSystemItem;
	bool	ListOSProcess();
	void	ItemClickNotify(HANDLE hItem,int Col);
#endif
};


#endif

