#ifndef _SEHCHAINWND_H_
#define _SEHCHAINWND_H_
typedef struct _SEHCHAIN 
{
	DWORD Next;
	DWORD Handler;
}SEHCHAIN,*PSEHCHAIN;
class CSEHChainWnd:public CWispList
{
public:
	CSEHChainWnd();
	~CSEHChainWnd();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG_EVENT_MAP
	void UpdateContext();
};
#endif //_SEHCHAINWND_H_