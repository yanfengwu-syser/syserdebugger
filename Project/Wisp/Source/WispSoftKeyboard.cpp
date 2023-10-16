#include "StdAfx.h"
#include "WispSoftKeyboard.h"
#include "WispButton.h"
#include "WispCheckBox.h"


#define	WISP_SKB_BT_COUNT	(sizeof(m_SoftKeyTable)/sizeof(WISP_SKB_KEY))

WISP_SKB_KEY CWispSoftKeyboard::m_SoftKeyTable[]=
{
	{WISP_STR("ESC"),	WISP_VK_ESCAPE,		{2		,2,22,20}},

	{WISP_STR("F1"),	WISP_VK_F1,			{24*2-2	,2,22,20}},
	{WISP_STR("F2"),	WISP_VK_F2,			{24*3-2	,2,22,20}},
	{WISP_STR("F3"),	WISP_VK_F3,			{24*4-2	,2,22,20}},
	{WISP_STR("F4"),	WISP_VK_F4,			{24*5-2	,2,22,20}},

	{WISP_STR("F5"),	WISP_VK_F5,			{24*7-10,2,22,20}},
	{WISP_STR("F6"),	WISP_VK_F6,			{24*8-10,2,22,20}},
	{WISP_STR("F7"),	WISP_VK_F7,			{24*9-10,2,22,20}},
	{WISP_STR("F8"),	WISP_VK_F8,			{24*10-10,2,22,20}},

	{WISP_STR("F9"),	WISP_VK_F9,			{24*11+2,2,22,20}},
	{WISP_STR("F10"),	WISP_VK_F10,		{24*12+2,2,22,20}},
	{WISP_STR("F11"),	WISP_VK_F11,		{24*13+2,2,22,20}},
	{WISP_STR("F12"),	WISP_VK_F12,		{24*14+2,2,22,20}},

	{WISP_STR("`"),		WISP_VK_OEM_3,		{2		,6+22,22,20}},
	{WISP_STR("1"),		WISP_VK_1,			{2+24*1	,6+22,22,20}},
	{WISP_STR("2"),		WISP_VK_2,			{2+24*2	,6+22,22,20}},
	{WISP_STR("3"),		WISP_VK_3,			{2+24*3	,6+22,22,20}},
	{WISP_STR("4"),		WISP_VK_4,			{2+24*4	,6+22,22,20}},
	{WISP_STR("5"),		WISP_VK_5,			{2+24*5	,6+22,22,20}},
	{WISP_STR("6"),		WISP_VK_6,			{2+24*6	,6+22,22,20}},
	{WISP_STR("7"),		WISP_VK_7,			{2+24*7	,6+22,22,20}},
	{WISP_STR("8"),		WISP_VK_8,			{2+24*8	,6+22,22,20}},
	{WISP_STR("9"),		WISP_VK_9,			{2+24*9	,6+22,22,20}},
	{WISP_STR("0"),		WISP_VK_0,			{2+24*10,6+22,22,20}},
	{WISP_STR("-"),		WISP_VK_SUBTRACT,	{2+24*11,6+22,22,20}},
	{WISP_STR("="),		WISP_VK_OEM_PLUS,	{2+24*12,6+22,22,20}},
	{WISP_STR("\\"),	WISP_VK_SEPARATOR,	{2+24*13,6+22,22,20}},
	{WISP_STR("<-"),	WISP_VK_BACK,		{2+24*14,6+22,22,20}},

	{WISP_STR("TAB"),	WISP_VK_TAB,		{2			,6+22*2,32,20}},
	{WISP_STR("Q"),		WISP_VK_Q,			{2+34		,6+22*2,22,20}},
	{WISP_STR("W"),		WISP_VK_W,			{2+34+24	,6+22*2,22,20}},
	{WISP_STR("E"),		WISP_VK_E,			{2+34+24*2	,6+22*2,22,20}},
	{WISP_STR("R"),		WISP_VK_R,			{2+34+24*3	,6+22*2,22,20}},
	{WISP_STR("T"),		WISP_VK_T,			{2+34+24*4	,6+22*2,22,20}},
	{WISP_STR("Y"),		WISP_VK_Y,			{2+34+24*5	,6+22*2,22,20}},

	{WISP_STR("U"),		WISP_VK_U,				{2+34+24*6	,6+22*2,22,20}},
	{WISP_STR("I"),		WISP_VK_I,				{2+34+24*7	,6+22*2,22,20}},
	{WISP_STR("O"),		WISP_VK_O,				{2+34+24*8	,6+22*2,22,20}},
	{WISP_STR("P"),		WISP_VK_P,				{2+34+24*9	,6+22*2,22,20}},
	{WISP_STR("["),		WISP_VK_LSQUARE_BRACKET,{2+34+24*10	,6+22*2,22,20}},
	{WISP_STR("]"),		WISP_VK_RSQUARE_BRACKET,{2+34+24*11	,6+22*2,22,20}},

	{WISP_STR("Caps"),	WISP_VK_CAPS_LOCK,	{2			,6+22*3,40,20}},
	{WISP_STR("A"),		WISP_VK_A,			{2+42		,6+22*3,22,20}},
	{WISP_STR("S"),		WISP_VK_S,			{2+42+24	,6+22*3,22,20}},
	{WISP_STR("D"),		WISP_VK_D,			{2+42+24*2	,6+22*3,22,20}},
	{WISP_STR("F"),		WISP_VK_F,			{2+42+24*3	,6+22*3,22,20}},
	{WISP_STR("G"),		WISP_VK_G,			{2+42+24*4	,6+22*3,22,20}},
	{WISP_STR("H"),		WISP_VK_H,			{2+42+24*5	,6+22*3,22,20}},
	{WISP_STR("J"),		WISP_VK_J,			{2+42+24*6	,6+22*3,22,20}},
	{WISP_STR("K"),		WISP_VK_K,			{2+42+24*7	,6+22*3,22,20}},
	{WISP_STR("L"),		WISP_VK_L,			{2+42+24*8	,6+22*3,22,20}},
	{WISP_STR(";"),		WISP_VK_SEMI,		{2+42+24*9	,6+22*3,22,20}},
	{WISP_STR("'"),		WISP_VK_QUOT,		{2+42+24*10	,6+22*3,22,20}},
	{WISP_STR("Enter"),WISP_VK_RETURN,		{2+42+24*11	,6+22*3,52,20}},

	{WISP_STR("Shift"),WISP_VK_LSHIFT,		{2			,6+22*4,50,20}},
	{WISP_STR("Z"),		WISP_VK_Z,			{2+52		,6+22*4,22,20}},
	{WISP_STR("X"),		WISP_VK_X,			{2+52+24	,6+22*4,22,20}},
	{WISP_STR("C"),		WISP_VK_C,			{2+52+24*2	,6+22*4,22,20}},
	{WISP_STR("V"),		WISP_VK_V,			{2+52+24*3	,6+22*4,22,20}},
	{WISP_STR("B"),		WISP_VK_B,			{2+52+24*4	,6+22*4,22,20}},
	{WISP_STR("N"),		WISP_VK_N,			{2+52+24*5	,6+22*4,22,20}},
	{WISP_STR("M"),		WISP_VK_M,			{2+52+24*6	,6+22*4,22,20}},
	{WISP_STR(","),		WISP_VK_OEM_COMMA,	{2+52+24*7	,6+22*4,22,20}},
	{WISP_STR("."),		WISP_VK_OEM_PERIOD,	{2+52+24*8	,6+22*4,22,20}},
	{WISP_STR("/"),		WISP_VK_DIVIDE,		{2+52+24*9	,6+22*4,22,20}},
	{WISP_STR("Shift"),WISP_VK_RSHIFT,		{2+52+24*10	,6+22*4,66,20}},

	{WISP_STR("Ctrl"),	WISP_VK_LCONTROL,	{2			,6+22*5,32,20}},
	{WISP_STR("Win"),	WISP_VK_LWIN,		{2+34		,6+22*5,32,20}},
	{WISP_STR("Alt"),	WISP_VK_LALT,		{2+34*2		,6+22*5,32,20}},
	{WISP_STR("Space"),WISP_VK_SPACE,		{2+34*3		,6+22*5,34*3+18,20}},
	{WISP_STR("Alt"),	WISP_VK_RALT,		{2+34*6+20	,6+22*5,32,20}},
	{WISP_STR("Win"),	WISP_VK_RWIN,		{2+34*7+20	,6+22*5,32,20}},
	{WISP_STR("Apps"),	WISP_VK_APPS,		{2+34*8+20	,6+22*5,32,20}},
	{WISP_STR("Ctrl"),	WISP_VK_RCONTROL,	{2+34*9+20	,6+22*5,32,20}},

	{WISP_STR("Ins"),	WISP_VK_INSERT,		{6+24*15		,6+22*2,24,20}},
	{WISP_STR("Hom"),	WISP_VK_HOME,		{6+24*15+26		,6+22*2,24,20}},
	{WISP_STR("PUp"),	WISP_VK_PAGE_UP,	{6+24*15+26*2	,6+22*2,24,20}},

	{WISP_STR("Del"),	WISP_VK_DELETE,		{6+24*15		,6+22*3,24,20}},
	{WISP_STR("End"),	WISP_VK_END,		{6+24*15+26		,6+22*3,24,20}},
	{WISP_STR("PDo"),	WISP_VK_PAGE_DOWN,	{6+24*15+26*2	,6+22*3,24,20}},

	{WISP_STR("Up"),	WISP_VK_LEFT,	{6+24*15+26		,6+22*4,24,20}},

	{WISP_STR("Le"),	WISP_VK_LEFT,	{6+24*15		,6+22*5,24,20}},
	{WISP_STR("Do"),	WISP_VK_DOWN,	{6+24*15+26		,6+22*5,24,20}},
	{WISP_STR("Ri"),	WISP_VK_RIGHT,	{6+24*15+26*2	,6+22*5,24,20}},
};

WISP_MSG_MAP_BEGIN(CWispSoftKeyboard)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_GET_FOCUS,OnGetFocus)
WISP_MSG_MAP_END(CWispWnd)

CWispSoftKeyboard::CWispSoftKeyboard(void)
{
}

CWispSoftKeyboard::~CWispSoftKeyboard(void)
{
}

void CWispSoftKeyboard::Popup()
{
	if(IsWindow())
	{
		Show();
	}
	else
	{
		Create(0,0,NULL,WISP_SKBS_NORMAL,WISP_SH_NORMAL);
		Center();
	}
}

bool CWispSoftKeyboard::Create(int x,int y,CWispWnd*pParentWnd,UINT Style,UINT ShowMode,UINT CmdID)
{
	return CWispWnd::Create(WISP_STR("Soft Keyboard"),CWispRect(x,y,453,166),pParentWnd,CmdID,Style,ShowMode);
}

bool CWispSoftKeyboard::OnCreate(IN WISP_MSG*pMsg)
{
	LoadTitleDIB("\\WispApp\\SoftKeyboard\\SoftKeyboard.ico");
	m_StaticDIB.Create(WispDIB("\\WispApp\\SoftKeyboard\\SoftKeyboard.ico",0),387,8,this);
	m_BTAry = new CWispBaseWnd*[WISP_SKB_BT_COUNT];
	for(int n=0;n<WISP_SKB_BT_COUNT;n++)
	{
		if(m_SoftKeyTable[n].VKCmdID==WISP_VK_RSHIFT || m_SoftKeyTable[n].VKCmdID==WISP_VK_LSHIFT)
		{
			m_BTAry[n]= new CWispCheckBox;
			m_BTAry[n]->Create(m_SoftKeyTable[n].szKeyName,&m_SoftKeyTable[n].BTRect,this,m_SoftKeyTable[n].VKCmdID,WISP_CBS_PUSHLIKE,WISP_SH_NORMAL);
		}
		else
		{
			m_BTAry[n]= new CWispButton;
			m_BTAry[n]->Create(m_SoftKeyTable[n].szKeyName,&m_SoftKeyTable[n].BTRect,this,m_SoftKeyTable[n].VKCmdID,WISP_BS_NORMAL,WISP_SH_NORMAL);
		}
	}
	return true;
}

bool CWispSoftKeyboard::OnDestroy(IN WISP_MSG*pMsg)
{
	for(int n=0;n<WISP_SKB_BT_COUNT;n++)
	{
		m_BTAry[n]->Destroy();
		delete m_BTAry[n];
	}
	delete[] m_BTAry;
	return true;
}

bool CWispSoftKeyboard::OnKeyEvent(IN WISP_MSG*pMsg)
{
	return true;
}

bool CWispSoftKeyboard::OnGetFocus(IN WISP_MSG*pMsg)
{
	Top();
	return false;
}

bool CWispSoftKeyboard::OnCommand(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg==WISP_CMD_CTRL_GET_FOCUS)
		return false;
	if(pMsg->Command.CmdID<WISP_VK_MAX_ID)
	{
		m_pWispBase->DispatchKeyEvent(pMsg->Command.CmdID,pMsg->Command.CmdMsg == WISP_CMD_BT_DOWN);
	}
	return true;
}

