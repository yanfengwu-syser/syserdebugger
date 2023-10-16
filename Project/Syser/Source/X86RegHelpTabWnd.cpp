#include "StdAfx.h"
#include "Syser.h"
#include "X86RegHelpTabWnd.h"
 
WISP_MSG_MAP_BEGIN(CX86RegHelpTabWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP_END(CWispTabWnd)

CX86RegHelpTabWnd::CX86RegHelpTabWnd(void)
{
}

CX86RegHelpTabWnd::~CX86RegHelpTabWnd(void)
{
}

void CX86RegHelpTabWnd::Popup()
{
	if(IsWindow())
	{
		Show();
	}
	else
	{
		Create(WISP_STR("Register Help Wnd"),CWispRect(0,0,560,400));
		Center();
	}
}

bool CX86RegHelpTabWnd::OnCreate(IN WISP_MSG *pMsg)
{
	m_RegisterGroup[0].Create(WSTR("Control Register"),CWispRect(0,0,0,0),this,0,WISP_WS_NULL);
	m_RegisterGroup[0].SetRegisterGroup(CONTROL_REGISTER);
	InsertWnd(WSTR("Control"),&m_RegisterGroup[0]);
	m_RegisterGroup[1].Create(WSTR("Debug Register"),CWispRect(0,0,0,0),this,0,WISP_WS_NULL);
	m_RegisterGroup[1].SetRegisterGroup(DEBUG_REGISTER);
	InsertWnd(WSTR("Debug"),&m_RegisterGroup[1]);
	m_RegisterGroup[2].Create(WSTR("Segment Descriptor"),CWispRect(0,0,0,0),this,0,WISP_WS_NULL);
	m_RegisterGroup[2].SetRegisterGroup(SEGMENT_DESCRIPTOR_REGISTER);
	InsertWnd(WSTR("Segment Descriptor"),&m_RegisterGroup[2]);
	m_RegisterGroup[3].Create(WSTR("Flags Register"),CWispRect(0,0,0,0),this,0,WISP_WS_NULL);
	m_RegisterGroup[3].SetRegisterGroup(FLAGS_REGISTER);
	InsertWnd(WSTR("Flags Register"),&m_RegisterGroup[3]);
	m_RegisterGroup[4].Create(WSTR("Flags Register"),CWispRect(0,0,0,0),this,0,WISP_WS_NULL);
	m_RegisterGroup[4].SetRegisterGroup(PAGEDIRENTRY4M_REGISTER);
	InsertWnd(WSTR("Page Directory Entry (4M)"),&m_RegisterGroup[4]);
	m_RegisterGroup[5].Create(WSTR("Flags Register"),CWispRect(0,0,0,0),this,0,WISP_WS_NULL);
	m_RegisterGroup[5].SetRegisterGroup(PAGEDIRENTRY4K_REGISTER);
	InsertWnd(WSTR("Page Map (4K)"),&m_RegisterGroup[5]);
	return true;
}

