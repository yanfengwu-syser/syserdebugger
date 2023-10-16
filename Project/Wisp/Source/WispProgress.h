#ifndef _WISP_PROGRESS_H_
#define _WISP_PROGRESS_H_

#include "WispBaseWnd.h"

#define PROGRESS_MARGIN		1

class CWispProgress : public CWispBaseWnd
{
protected:
	int m_nStep, m_nPos;
	int m_nLower, m_nUpper;
public:
	CWispProgress(void);
	~CWispProgress(void);
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdate)
public:
	void	GetRange(int& nLower, int& nUpper) { nLower=m_nLower; nUpper=m_nUpper; }
	int		GetPos() { return m_nPos; }
	void	SetPos(int nPos) { m_nPos = nPos; }
	void	SetRange(int nLower, int nUpper);
	void	SetStep(int nStep) { m_nStep = nStep; }
	void	StepIt();
	void	OffsetPos(int nOffset);
};

#endif
