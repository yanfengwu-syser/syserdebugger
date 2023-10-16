#ifndef _X86REGHELPTABWND_H_ 
#define _X86REGHELPTABWND_H_
#include "RegHelpWnd.h"

class CX86RegHelpTabWnd :public CWispTabWnd
{
public:
	CX86RegHelpTabWnd(void);
	~CX86RegHelpTabWnd(void);
	void	Popup();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClose)
	CRegHelpWnd m_RegisterGroup[MAX_REGISTER_GROUP_INDEX];
};

#endif /* _X86REGHELPTABWND_H_ */

