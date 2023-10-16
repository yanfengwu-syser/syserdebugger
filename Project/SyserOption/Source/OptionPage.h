#ifndef _OPTION_PAGE_H_
#define _OPTION_PAGE_H_

class COptionPage : public CWispOptionForm
{
public:
	COptionPage();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate);
	void OptionApplyNotify();
	bool OptionBeforeDefaultNotify();
	void OptionDefaultNotify();
};

#endif
