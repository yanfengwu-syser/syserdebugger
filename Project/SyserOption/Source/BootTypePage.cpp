#include "StdAfx.h"
#include "BootTypePage.h"


WISP_FORM_RES_ITEM CBootTypePage::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,500,400},
		WISP_ID_NULL,
		WISP_WS_NULL,
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CBootTypePage)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
//	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)


//WISP_MSG_CMD_MAP_BEGIN(CBootTypePage)
//WISP_MSG_CMD_MAP_END

CBootTypePage::CBootTypePage()
{
	m_pFormRes = m_FormRes;
}

CBootTypePage::~CBootTypePage()
{

}

bool CBootTypePage::OnFormCreate(IN WISP_MSG*pMsg)
{
	return true;
}

