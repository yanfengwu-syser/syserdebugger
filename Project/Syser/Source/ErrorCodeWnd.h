#ifndef _ERROR_CODE_WND_H_
#define _ERROR_CODE_WND_H_
class CErrorCodeWnd:public CWispList
{
public:
	CErrorCodeWnd();
	~CErrorCodeWnd();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG_EVENT_MAP
	void UpdateContext();
};
#endif //_MODULE_LIST_WND_