#include "StdAfx.h"
#include "WispProgress.h"

WISP_MSG_MAP_BEGIN(CWispProgress)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)
WISP_MSG_MAP_END(CWispBaseWnd)

CWispProgress::CWispProgress(void)
{
	m_nStep	= 1;
	m_nPos	= 0;
	m_nLower= 0;
	m_nUpper= 9;
	m_CtrlType = WISP_CTRL_PROGRESS;
}

CWispProgress::~CWispProgress(void)
{
}

bool CWispProgress::OnUpdate(IN WISP_MSG*pMsg)
{
	WISP_RECT Rect;
	Rect.x = Rect.y = 0;
	Rect.cx = m_WindowRect.cx;
	Rect.cy = m_WindowRect.cy;

	if( !(m_Style&WISP_WS_BACK_TRANS) )
		m_pWispBase->m_pCurDrawObj->DrawCtrlClient(&m_WindowDC, &Rect);

	int nPrecent = m_nPos*1000/(m_nUpper-m_nLower);
	m_pWispBase->m_pCurDrawObj->DrawProgress(&m_WindowDC, &Rect, m_Style, nPrecent);
	return true;
}


void CWispProgress::SetRange(int nLower, int nUpper)
{
	CODE_ASSERT(nUpper>nLower);
	m_nLower = nLower;
	m_nUpper = nUpper;
	Update();
}

void CWispProgress::StepIt()
{
	m_nPos += m_nStep;
	if(m_nPos>m_nUpper)
		m_nPos = m_nLower;
	else if(m_nPos<m_nLower)
		m_nPos = m_nUpper;
	Update();
}

void CWispProgress::OffsetPos(int nOffset)
{
	m_nPos+=nOffset;
	if(m_nPos>m_nUpper)
		m_nPos = m_nLower;
	else if(m_nPos<m_nLower)
		m_nPos = m_nUpper;
	Update();
}

