#include "StdAfx.h"
#include "WispTaskPanel.h"

const COLORREF clrBkgndBeginLunaBlue = RGB(123, 162, 231);
const COLORREF clrBkgndEndLunaBlue = RGB(99, 117, 214);

WISP_MSG_MAP_BEGIN(CWispTaskPanel)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_RECALCLAYOUT,OnRecalcLayout)
WISP_MSG_MAP_END(CWispWnd)

CWispTaskPanel::CWispTaskPanel()
{

}

CWispTaskPanel::~CWispTaskPanel()
{
}

bool CWispTaskPanel::OnUpdateClient(IN WISP_MSG*pMsg)
{
	CWispRect rc(&m_ClientRect);
	m_WindowDC.DrawFullRect(&rc,clrBkgndBeginLunaBlue);
	return false;
}

bool CWispTaskPanel::OnRecalcLayout(IN WISP_MSG*pMsg)
{
	return true;
}
