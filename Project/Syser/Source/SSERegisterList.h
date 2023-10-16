#ifndef _SSEREGISTERLIST_H_
#define _SSEREGISTERLIST_H_

enum SSE_REG_INDEX
{
	SSE_REG_0,
	SSE_REG_1,
	SSE_REG_2,
	SSE_REG_3,
	SSE_REG_4,
	SSE_REG_5,
	SSE_REG_6,
	SSE_REG_7,
	SSE_REG_COUNT,
};


class CSSERegisterList : public CWispList
{
	HANDLE	m_hSSE128RegItem[SSE_REG_COUNT];
	DWORD	m_OldXMMRegister[8][4];
	COLORREF	m_ChgColor;
	COLORREF	m_NormalColor;
public:
	CSSERegisterList(void);
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnGetFocus)
	void UpdateContext();
	void ResetContext();
	int GetCPUIndex()const {return m_nCPUIndex;}
	void SetCPUIndex(int Index) {m_nCPUIndex=Index;}
private:
	int	m_nCPUIndex;

};

#endif
