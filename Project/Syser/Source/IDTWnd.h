#ifndef _IDTWND_H_
#define _IDTWND_H_

class CIDTWnd :	public CWispList
{
public:
	CIDTWnd();
	~CIDTWnd();
	void	Popup();
	void	UpdateContext();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnClose);
	bool	InsertIDT();
	void	SetIDTBaseAddress(void *IDTBase,DWORD dwIDTSize=0x7ff,DWORD dwIndex=0);
	static BYTE idtdata[8*256];
	VOID *	m_pIDTAddress;
	DWORD	m_dwIDTSize;
	DWORD	m_dwBeginIndex;
};
 
#endif
