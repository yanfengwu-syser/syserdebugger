#ifndef _MAIN_FRAME_H_
#define _MAIN_FRAME_H_

#include "OptionPage.h"
#include "CmdEditPage.h"
#include "SDSFilePage.h"
#include "GUIColorPage.h"
#include "ExportModulePage.h"
#include "../../syser/Source/KeyMappingPage.h"

class CMainFrame : public CWispWnd
{
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnSize);
public:
	COptionPage		m_OptionPage;
	CCmdEditPage	m_CmdEditPage;
	CWispTabWnd		m_MainTabWnd;
	CGUIColorPage	m_GUIColorPage;
	CSDSFilePage	m_SDSFilePage;
	CExportModulePage	m_ExportModulePage;
	CKeyMappingPage m_KeyMappingPage;
};

#endif
