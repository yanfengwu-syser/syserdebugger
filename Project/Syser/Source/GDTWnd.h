#ifndef _GDTWND_H_
#define _GDTWND_H_
 
class CGDTWnd :	public CWispList
{
public:
	CGDTWnd();
	~CGDTWnd();
	void	Popup();
	void	UpdateContext();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnClose);
	bool	InsertGDT();
	void	SetGDTBaseAddress(void *GDTBase,DWORD dwGDTSize=0x7ff,DWORD dwIndex=0);
	static BYTE gdtdata[8*256];
	VOID *	m_pGDTAddress;
	DWORD	m_dwGDTSize;
	DWORD	m_dwBeginIndex;
};

#endif /* _GDTWND_H_ */

