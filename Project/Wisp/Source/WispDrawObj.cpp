#include "StdAfx.h"
#include "WispWnd.h"
#include "WispDrawObj.h"
#include "DIBData.h"
#include "WispMenu.h"
#include "WispList.h"

CWispDrawObj::CWispDrawObj()
{
	InitSystemColor();
}

CWispDrawObj::~CWispDrawObj()
{
}

void CWispDrawObj::InitSystemColor()
{
	m_crSystem[SC_BLACK			]					= WISP_RGB(0,0,0);
	m_crSystem[SC_WHITE			]					= WISP_RGB(255,255,255);
	m_crSystem[SC_RED			]					= WISP_RGB(192,0,0);
	m_crSystem[SC_LIGHT_RED		]					= WISP_RGB(255,0,0);
	m_crSystem[SC_GREEN			]					= WISP_RGB(0,192,0);
	m_crSystem[SC_LIGHT_GREEN	]					= WISP_RGB(0,255,128);
	m_crSystem[SC_BLUE			]					= WISP_RGB(0,0,192);
	m_crSystem[SC_LIGHT_BLUE	]					= WISP_RGB(0,128,255);
	m_crSystem[SC_BROWN			]					= WISP_RGB(128,64,64);
	m_crSystem[SC_LIGHT_BROWN	]					= WISP_RGB(200,100,100);
	m_crSystem[SC_CYAN			]					= WISP_RGB(0,192,192);
	m_crSystem[SC_LIGHT_CYAN	]					= WISP_RGB(0,255,255);
	m_crSystem[SC_GRAY			]					= WISP_RGB(128,128,128);
	m_crSystem[SC_LIGHT_GRAY	]					= WISP_RGB(200,200,200);
	m_crSystem[SC_YELLOW		]					= WISP_RGB(192,192,0);
	m_crSystem[SC_LIGHT_YELLOW	]					= WISP_RGB(255,255,0);
	m_crSystem[SC_ORANGE_RED	]					= WISP_RGB(128,64,0);
	m_crSystem[SC_LIGHT_ORANGE_RED]					= WISP_RGB(255,128,0);
	m_crSystem[SC_DESKTOP_BG	]					= WISP_RGB(0,0,0);
	m_crSystem[SC_DISABLE_BG	]					= WISP_RGB(200,200,200);
	m_crSystem[SC_CLIENT_BG		]					= WISP_RGB(236,233,216);
	m_crSystem[SC_CLIENT_TEXT	]					= WISP_RGB(0,0,0);
	m_crSystem[SC_CAPTION_TEXT	]					= WISP_RGB(255,255,255);
	m_crSystem[SC_CAPTION_BG	]					= WISP_RGB(35,152,200);
	m_crSystem[SC_CAPTION_LIGHT_BG]					= WISP_RGB(80,176,255);
	m_crSystem[SC_SELECT_BG		]					= WISP_RGB(0,128,255);
	m_crSystem[SC_SCROLL_SLIDE_BG]					= WISP_RGB(100,200,250);
	m_crSystem[SC_SCROLL_SLIDE_DARK_BG]				= WISP_RGB(60,140,220);
	m_crSystem[SC_BORDER_BG		]					= WISP_RGB(0,130,230);
	m_crSystem[SC_BRIGHT		]					= WISP_RGB(220,220,220);
	m_crSystem[SC_SHADOW		]					= WISP_RGB(85,85,85);
	m_crSystem[SC_SHADOW_LIGHT	]					= WISP_RGB(170,170,170);
	m_crSystem[SC_SCROLL_BG		]					= WISP_RGB(80,230,255);
	m_crSystem[SC_SCROLL_BT_BG	]					= WISP_RGB(50,180,230);
	m_crSystem[SC_CURSOR	]						= WISP_RGB(0,0,255);
	m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT	]	= WISP_RGB(127,157,185);
	m_crSystem[SC_CTRL_NORMAL_BORDER_BOTTOMRIGHT]	= WISP_RGB(127,157,185);
	m_crSystem[SC_CTRL_NORMAL_DARK_BORDER		]	= WISP_RGB(28,81,128);
	m_crSystem[SC_CTRL_NORMAL_CLIENT_BG			]	= WISP_RGB(255,255,255);
	m_crSystem[SC_CTRL_NORMAL_DARK_CLIENT_BG	]	= WISP_RGB(243,243,239);
	m_crSystem[SC_CTRL_NORMAL_DARK_CLIENT_BG2	]	= WISP_RGB(226,225,218);
	m_crSystem[SC_CTRL_SELECTED_BG		]			= WISP_RGB(160,160,160);
	m_crSystem[SC_CTRL_SELECTED_LIGHT_BG]			= WISP_RGB(192,192,192);
	m_crSystem[SC_CTRL_HOVER_BG			]			= WISP_RGB(248,179,48);
	m_crSystem[SC_CTRL_HOVER_LIGHT_BG	]			= WISP_RGB(255,214,100);
	m_crSystem[SC_CTRL_SELECTED_TEXT	]			= WISP_RGB(255,255,255);
	m_crSystem[SC_CTRL_NORMAL_TEXT		]			= WISP_RGB(0,0,0);
	m_crSystem[SC_CTRL_HOVER_TEXT		]			= WISP_RGB(0,0,128);
	m_crSystem[SC_CTRL_NORMAL_FOCUS		]			= WISP_RGB(0,0,255);
	m_crSystem[SC_CTRL_HOVER_FOCUS		]			= WISP_RGB(49,106,197);
	m_crSystem[SC_MENU_BG		]					= WISP_RGB(180,200,228);
	m_crSystem[SC_MENU_LIGHT_BG	]					= WISP_RGB(210,230,255);
	m_crSystem[SC_MENU_BORDER	]					= WISP_RGB(138,134,122);
	m_crSystem[SC_STDICON_NORMAL_BORDER		]		= WISP_RGB(80,176,255);
	m_crSystem[SC_STDICON_HOVER_BORDER		]		= WISP_RGB(0,255,255);
	m_crSystem[SC_STDICON_DOWN_BORDER		]		= WISP_RGB(255,255,255);
	m_crSystem[SC_STDICON_NORMAL_CHECKMARK	]		= WISP_RGB(33,161,33);
	m_crSystem[SC_STDICON_NORMAL_PLUS		]		= WISP_RGB(0,0,0);
	m_crSystem[SC_SCROLL_NORMAL_BUTTON		]		= WISP_RGB(118,177,229);
	m_crSystem[SC_SCROLL_HOVER_BUTTON		]		= WISP_RGB(180,214,241);
	m_crSystem[SC_SCROLL_DOWN_BUTTON		]		= WISP_RGB(100,146,185);
	m_crSystem[SC_FRAME_NORMAL_BG		]			= WISP_RGB(235,234,219);
	m_crSystem[SC_FRAME_NORMAL_LEFT		]			= WISP_RGB(255,255,255);
	m_crSystem[SC_FRAME_NORMAL_RIGHT	]			= WISP_RGB(199,197,178);
	m_crSystem[SC_FRAME_NORMAL_BOTTOM1	]			= WISP_RGB(226,222,205);
	m_crSystem[SC_FRAME_NORMAL_BOTTOM2	]			= WISP_RGB(214,210,194);
	m_crSystem[SC_FRAME_NORMAL_BOTTOM3	]			= WISP_RGB(203,199,184);
	m_crSystem[SC_FRAME_HOVER_BG		]			= WISP_RGB(243,243,243);
	m_crSystem[SC_FRAME_HOVER_BOTTOM1	]			= WISP_RGB(248,169,0);
	m_crSystem[SC_FRAME_HOVER_BOTTOM2	]			= WISP_RGB(249,198,84);
	m_crSystem[SC_FRAME_HOVER_BOTTOM3	]			= WISP_RGB(248,179,31);
	m_crSystem[SC_GRADIENT_GREEN_1	]				= WISP_RGB(171,237,172);
	m_crSystem[SC_GRADIENT_GREEN_2	]				= WISP_RGB(149,233,150);
	m_crSystem[SC_GRADIENT_GREEN_3	]				= WISP_RGB(124,228,126);
	m_crSystem[SC_GRADIENT_GREEN_4	]				= WISP_RGB(102,223,104);
	m_crSystem[SC_GRADIENT_GREEN_5	]				= WISP_RGB(78,218,80);
	m_crSystem[SC_GRADIENT_GREEN_6	]				= WISP_RGB(53,213,56);
	m_crSystem[SC_GRADIENT_GREEN_7	]				= WISP_RGB(40,210,43);

	m_crSystem[SC_GRADIENT_YELLOW	]				= WISP_RGB(200,130,0);
	m_crSystem[SC_GRADIENT_YELLOW_1	]				= WISP_RGB(229,151,0);
	m_crSystem[SC_GRADIENT_YELLOW_2	]				= WISP_RGB(248,179,48);
	m_crSystem[SC_GRADIENT_YELLOW_3	]				= WISP_RGB(253,216,137);

	m_crSystem[SC_GRADIENT_BULE_1	]				= WISP_RGB(61,149,255);
	m_crSystem[SC_GRADIENT_BULE_2	]				= WISP_RGB(43,144,255);
	m_crSystem[SC_GRADIENT_BULE_3	]				= WISP_RGB(0,85,234);
	m_crSystem[SC_GRADIENT_BULE_4	]				= WISP_RGB(0,70,224);
	m_crSystem[SC_GRADIENT_BULE_5	]				= WISP_RGB(1,67,207);
	m_crSystem[SC_GRADIENT_BULE_6	]				= WISP_RGB(0,61,220);
	m_crSystem[SC_GRADIENT_BULE_7	]				= WISP_RGB(0,29,160);
	m_crSystem[SC_GRADIENT_BULE_8	]				= WISP_RGB(0,19,140);

	m_crSystem[SC_RAV_1				]				= WISP_RGB(123,123,123);
	m_crSystem[SC_RAV_2				]				= WISP_RGB(224,232,254);
	m_crSystem[SC_RAV_3				]				= WISP_RGB(241,241,241);
	m_crSystem[SC_RAV_4				]				= WISP_RGB(231,235,255);
	m_crSystem[SC_RAV_5				]				= WISP_RGB(107,121,189);
	m_crSystem[SC_UNNAMED_1			]				= WISP_RGB(172,168,153);
	m_crSystem[SC_UNNAMED_2			]				= WISP_RGB(241,239,226);
	m_crSystem[SC_UNNAMED_3			]				= WISP_RGB(113,111,100);
	m_crSystem[SC_UNNAMED_4			]				= WISP_RGB(222,223,216);
	m_crSystem[SC_UNNAMED_5			]				= WISP_RGB(165,165,151);
	m_crSystem[SC_UNNAMED_6			]				= WISP_RGB(193,194,184);
	m_crSystem[SC_UNNAMED_7			]				= WISP_RGB(208,209,201);
	m_crSystem[SC_UNNAMED_8			]				= WISP_RGB(180,250,212);
	m_crSystem[SC_UNNAMED_9			]				= WISP_RGB(100,200,255);
	m_crSystem[SC_UNNAMED_10		]				= WISP_RGB(255,170,170);
	m_crSystem[SC_UNNAMED_11		]				= WISP_RGB(0,155,255);
	m_crSystem[SC_UNNAMED_12		]				= WISP_RGB(180,40,40);
	m_crSystem[SC_UNNAMED_13		]				= WISP_RGB(112,162,243);
	m_crSystem[SC_UNNAMED_14		]				= WISP_RGB(197,194,184);
	m_crSystem[SC_UNNAMED_15		]				= WISP_RGB(0,255,0);
	m_crSystem[SC_UNNAMED_16		]				= WISP_RGB(255,0,255);
	m_crSystem[SC_UNNAMED_17		]				= WISP_RGB(250,250,204);
	m_crSystem[SC_UNNAMED_18		]				= WISP_RGB(33,162,33);
	m_crSystem[SC_UNNAMED_19		]				= WISP_RGB(123,162,231);
	m_crSystem[SC_UNNAMED_20		]				= WISP_RGB(99,117,214);	
	m_crSystem[SC_UNNAMED_21		]				= WISP_RGB(180,177,163);	
}

bool CWispDrawObj::Init()
{
	gpCurWisp->m_MouseSize.cx = gpCurWisp->m_MouseSize.cy = 16;
	return true;
}

void CWispDrawObj::Release()
{

}

void CWispDrawObj::DrawBorder(CWispDC*pDC,WISP_RECT*pRect,int Size)
{
	CWispRect rc(*pRect);
	if(Size>=1)
	{
		pDC->DrawRoundRect(&rc, m_crSystem[SC_BORDER_BG]);
		rc.DeflateRect(1, 1);
	}
	if(Size>=2)
	{
		pDC->DrawRect(&rc, m_crSystem[SC_BORDER_BG]);
		rc.DeflateRect(1, 1);
	}

	if(Size>=3)
	{
		Size -= 3;
		for(int i=0; i<Size; i++)
		{
			pDC->DrawRect(&rc, m_crSystem[SC_BORDER_BG]);
			rc.DeflateRect(1, 1);
		}
	}
	if(Size>=1)
		pDC->DrawRect(&rc, m_crSystem[SC_BORDER_BG]);
}

void CWispDrawObj::DrawCaption(CWispDC*pDC,WISP_RECT*pRect)
{
	CWispRect rc(pRect);
	pDC->DrawFullRect(&rc, m_crSystem[SC_CAPTION_BG]);
}

void CWispDrawObj::DrawToolbarBK(CWispDC*pDC,WISP_RECT*pRect)
{
	pDC->DrawFullRect(pRect,m_crSystem[SC_CAPTION_LIGHT_BG]);
}

void CWispDrawObj::DrawClient(CWispDC*pDC,WISP_RECT*pRect)
{
	pDC->DrawFullRect(pRect, m_crSystem[SC_CLIENT_BG]);
}

void CWispDrawObj::DrawCtrlBorder(CWispDC* pDC, WISP_RECT* pRect, int nSize)
{
	CWispRect	rc(pRect);
	for(int i=0; i<nSize-1; i++)
	{
		pDC->Draw3DRect(&rc, m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT], m_crSystem[SC_CTRL_NORMAL_BORDER_BOTTOMRIGHT]);
		rc.DeflateRect(1, 1);
	}
	pDC->DrawRect(&rc, m_crSystem[SC_CTRL_NORMAL_CLIENT_BG]);
}

void CWispDrawObj::DrawCtrlClient(CWispDC* pDC, WISP_RECT* pRect)
{
	if(pDC->m_pWispWnd->m_Style&WISP_WS_DISABLED)
		pDC->DrawFullRect(pRect, m_crSystem[SC_DISABLE_BG]);
	else
		pDC->DrawFullRect(pRect, m_crSystem[SC_CTRL_NORMAL_CLIENT_BG]);
}

void CWispDrawObj::DrawCtrlFocusRect(CWispDC* pDC, WISP_RECT* pRect)
{
	pDC->DrawDashRect(pRect, m_crSystem[SC_CTRL_NORMAL_FOCUS]);
}

void CWispDrawObj::DrawCtrlStaticEdge(CWispDC* pDC, WISP_RECT* pRect)
{
	COLORREF rcTopLef=m_crSystem[SC_UNNAMED_1];
	COLORREF rcBottomRight=m_crSystem[SC_WHITE];
	pDC->DrawHLine(pRect->x,pRect->x+pRect->cx-2,pRect->y,rcTopLef);
	pDC->DrawHLine(pRect->x,pRect->x+pRect->cx-1,pRect->y+pRect->cy-1,rcBottomRight);
	pDC->DrawVLine(pRect->x,pRect->y,pRect->y+pRect->cy-2,rcTopLef);
	pDC->DrawVLine(pRect->x+pRect->cx-1,pRect->y,pRect->y+pRect->cy-1,rcBottomRight);
}

void CWispDrawObj::DrawCtrlClientEdge(CWispDC* pDC, WISP_RECT* pRect)
{
	COLORREF rcTopLeft=m_crSystem[SC_UNNAMED_1];
	COLORREF rcTopLeft1=m_crSystem[SC_UNNAMED_3];
	COLORREF rcBottomRight=m_crSystem[SC_WHITE];
	COLORREF rcBottomRight1=m_crSystem[SC_UNNAMED_2];

	pDC->DrawHLine(pRect->x,pRect->x+pRect->cx-2,pRect->y,rcTopLeft);
	pDC->DrawHLine(pRect->x,pRect->x+pRect->cx-1,pRect->y+pRect->cy-1,rcBottomRight);
	pDC->DrawVLine(pRect->x,pRect->y,pRect->y+pRect->cy-2,rcTopLeft);
	pDC->DrawVLine(pRect->x+pRect->cx-1,pRect->y,pRect->y+pRect->cy-1,rcBottomRight);

	pDC->DrawHLine(pRect->x+1,pRect->x+pRect->cx-2-1,pRect->y+1,rcTopLeft1);
	pDC->DrawHLine(pRect->x+1,pRect->x+pRect->cx-1-1,pRect->y+pRect->cy-1-1,rcBottomRight1);
	pDC->DrawVLine(pRect->x+1,pRect->y+1,pRect->y+pRect->cy-2-1,rcTopLeft1);
	pDC->DrawVLine(pRect->x+pRect->cx-1-1,pRect->y+1,pRect->y+pRect->cy-1-1,rcBottomRight1);

}
void CWispDrawObj::DrawCtrlModalFrame(CWispDC* pDC, WISP_RECT* pRect)
{
	COLORREF rcTopLeft=m_crSystem[SC_UNNAMED_2];
	COLORREF rcTopLeft1=m_crSystem[SC_WHITE];
	COLORREF rcTopLeft2=m_crSystem[SC_CLIENT_BG];
	COLORREF rcBottomRight2=m_crSystem[SC_CLIENT_BG];
	COLORREF rcBottomRight1=m_crSystem[SC_UNNAMED_1];	
	COLORREF rcBottomRight=m_crSystem[SC_UNNAMED_3];

	pDC->DrawHLine(pRect->x,pRect->x+pRect->cx-2,pRect->y,rcTopLeft);
	pDC->DrawHLine(pRect->x,pRect->x+pRect->cx-1,pRect->y+pRect->cy-1,rcBottomRight);
	pDC->DrawVLine(pRect->x,pRect->y,pRect->y+pRect->cy-2,rcTopLeft);
	pDC->DrawVLine(pRect->x+pRect->cx-1,pRect->y,pRect->y+pRect->cy-1,rcBottomRight);

	pDC->DrawHLine(pRect->x+1,pRect->x+pRect->cx-2-1,pRect->y+1,rcTopLeft1);
	pDC->DrawHLine(pRect->x+1,pRect->x+pRect->cx-1-1,pRect->y+pRect->cy-1-1,rcBottomRight1);
	pDC->DrawVLine(pRect->x+1,pRect->y+1,pRect->y+pRect->cy-2-1,rcTopLeft1);
	pDC->DrawVLine(pRect->x+pRect->cx-1-1,pRect->y+1,pRect->y+pRect->cy-1-1,rcBottomRight1);
	
	pDC->DrawHLine(pRect->x+2,pRect->x+pRect->cx-2-2,pRect->y+2,rcTopLeft2);
	pDC->DrawHLine(pRect->x+2,pRect->x+pRect->cx-1-2,pRect->y+pRect->cy-1-2,rcBottomRight2);
	pDC->DrawVLine(pRect->x+2,pRect->y+2,pRect->y+pRect->cy-2-2,rcTopLeft2);
	pDC->DrawVLine(pRect->x+pRect->cx-1-2,pRect->y+2,pRect->y+pRect->cy-1-2,rcBottomRight2);
}

void CWispDrawObj::DrawVertScrollRect(CWispDC*pDC,WISP_RECT*pRect)
{
	pDC->DrawFullRect(pRect, m_crSystem[SC_CTRL_NORMAL_DARK_CLIENT_BG]);
}

void CWispDrawObj::DrawVertScrollSlideRect(CWispDC*pDC,WISP_RECT*pRect)
{
	CWispRect rc(pRect);
	pDC->DrawRoundRect(&rc, m_crSystem[SC_SCROLL_NORMAL_BUTTON]);
	rc.DeflateRect(1, 1);
	pDC->DrawRect(&rc, m_crSystem[SC_WHITE]);
	rc.DeflateRect(1, 1);
	pDC->DrawFullRect(&rc,m_crSystem[SC_SCROLL_SLIDE_BG]);
	if(rc.cy>=10)
	{
		for(int i=0; i<8; i+=2)
		{
			pDC->DrawHLine( rc.x+2, rc.x2()-2, (rc.cy-8)/2+rc.y+i, m_crSystem[SC_LIGHT_GRAY]);
			pDC->DrawHLine( rc.x+2, rc.x2()-2, (rc.cy-8)/2+rc.y+i+1,  m_crSystem[SC_GRAY]);
		}
	}
}

void CWispDrawObj::DrawHorzScrollRect(CWispDC*pDC,WISP_RECT*pRect)
{
	pDC->DrawFullRect(pRect, m_crSystem[SC_CTRL_NORMAL_DARK_CLIENT_BG]);
}

void CWispDrawObj::DrawHorzScrollSlideRect(CWispDC*pDC,WISP_RECT*pRect)
{
	CWispRect rc(pRect);
	pDC->DrawRoundRect(&rc, m_crSystem[SC_SCROLL_NORMAL_BUTTON]);
	rc.DeflateRect(1, 1);
	pDC->DrawRect(&rc, m_crSystem[SC_WHITE]);
	rc.DeflateRect(1, 1);
	pDC->DrawFullRect(&rc,m_crSystem[SC_SCROLL_SLIDE_BG]);
	if(rc.cx>=10)
	{
		for(int i=0; i<8; i+=2)
		{
			pDC->DrawVLine( (rc.cx-8)/2+rc.x+i, rc.y+2, rc.y2()-2,  m_crSystem[SC_LIGHT_GRAY]);
			pDC->DrawVLine( (rc.cx-8)/2+rc.x+i+1, rc.y+2, rc.y2()-2,  m_crSystem[SC_GRAY]);
		}
	}
}

void CWispDrawObj::DrawSplitRect(CWispDC*pDC,WISP_RECT*pRect,bool bHorz)
{	
	CWispWnd*pWnd=(CWispWnd*)pDC->m_pWispWnd;
	if(bHorz)
		pDC->DrawFullRect(pRect,m_crSystem[SC_BORDER_BG]);
	else
		pDC->DrawFullRect(pRect,m_crSystem[SC_BORDER_BG]);
}

void CWispDrawObj::DrawButtonClient(CWispDC*pDC,WISP_RECT*pRect,UINT State)
{
	if(State==STATUS_DOWN)
		pDC->DrawFullRect(pRect, m_crSystem[SC_CTRL_NORMAL_DARK_CLIENT_BG2]);
	else
		pDC->DrawFullRect(pRect, m_crSystem[SC_CTRL_NORMAL_DARK_CLIENT_BG]);
}

void CWispDrawObj::DrawButtonFrameRect(CWispDC*pDC,WISP_RECT*pRect,UINT State)
{
	if(State&WISP_WS_BACK_TRANS)
	{
		if(State == STATUS_DOWN)
			pDC->DrawFrameRect(pRect,false,1);
		if(State == STATUS_HOVER)
			pDC->DrawFrameRect(pRect,true,1);
	}
	else
	{
		switch(State)
		{
		case STATUS_HOVER:
			{
				CWispRect rc(*pRect);
				pDC->DrawRoundRect(pRect, m_crSystem[SC_CTRL_NORMAL_DARK_BORDER]);
				rc.DeflateRect(1,1);
				pDC->DrawRect(&rc, m_crSystem[SC_GRADIENT_YELLOW_2]);
				rc.DeflateRect(1,1);
				pDC->DrawRect(&rc, m_crSystem[SC_GRADIENT_YELLOW_3]);
			}
			break;
		case STATUS_NORMAL:
			{
				CWispRect rc(*pRect);
				pDC->DrawRoundRect(pRect, m_crSystem[SC_CTRL_NORMAL_DARK_BORDER]);
			}
			break;
		case STATUS_DOWN:
			{
				CWispRect rc(*pRect);
				rc.DeflateRect(1,1);
				pDC->DrawRoundRect(pRect, m_crSystem[SC_CTRL_NORMAL_DARK_BORDER]);
				pDC->DrawRect(&rc, m_crSystem[SC_CTRL_NORMAL_CLIENT_BG]);
			}
			break;
		case STATE_DISABLED:
			break;
		}
	}
}

void CWispDrawObj::DrawTabBackground(CWispDC* pDC, WISP_RECT* pRect)
{
	DrawToolbarBK(pDC,pRect);
}

void CWispDrawObj::DrawTabItem(CWispDC* pDC, WISP_RECT* pRect, UINT State)
{
	switch(State)
	{
	case STATUS_HOVER:
		{
			CWispRect rc(*pRect);
			rc.DeflateRect(1,1);
			pDC->DrawRect(&rc, m_crSystem[SC_GRADIENT_YELLOW_2]);
			rc.DeflateRect(1,1);
			pDC->DrawRect(&rc, m_crSystem[SC_GRADIENT_YELLOW_3]);
		}
	case STATUS_NORMAL:
	case STATUS_DOWN:
		pDC->DrawRoundRect(pRect, m_crSystem[SC_CTRL_NORMAL_DARK_BORDER]);
		break;
	case STATE_DISABLED:
		break;
	}
}

void CWispDrawObj::DrawHeaderFrameRect(CWispDC* pDC, WISP_RECT* pRect, UINT State)
{
	COLORREF crBk		= m_crSystem[SC_FRAME_NORMAL_BG		];
	COLORREF crLeft		= m_crSystem[SC_FRAME_NORMAL_LEFT	];
	COLORREF crRight	= m_crSystem[SC_FRAME_NORMAL_RIGHT	];
	COLORREF crBottom1	= m_crSystem[SC_FRAME_NORMAL_BOTTOM1];
	COLORREF crBottom2	= m_crSystem[SC_FRAME_NORMAL_BOTTOM2];
	COLORREF crBottom3	= m_crSystem[SC_FRAME_NORMAL_BOTTOM3];

	switch(State)
	{
	case STATUS_NORMAL:
		break;
	case STATUS_DOWN:
		{		
			crBk= m_crSystem[SC_UNNAMED_4];
			COLORREF crTop1= m_crSystem[SC_UNNAMED_5];
			COLORREF crTop2= m_crSystem[SC_UNNAMED_6];
			COLORREF crTop3=m_crSystem[SC_UNNAMED_7];
			pDC->DrawHLine(pRect->x+1, pRect->x+pRect->cx, pRect->y+pRect->cy-1, crTop1);
			pDC->DrawVLine(pRect->x+1,pRect->y, pRect->y+pRect->cy-1,crTop1);
			pDC->DrawFullRect(pRect, crBk);
		}
		return;
	case STATUS_HOVER:
		crBk		= m_crSystem[SC_FRAME_HOVER_BG		];
		crBottom1	= m_crSystem[SC_FRAME_HOVER_BOTTOM1	];
		crBottom2	= m_crSystem[SC_FRAME_HOVER_BOTTOM2	];
		crBottom3	= m_crSystem[SC_FRAME_HOVER_BOTTOM3	];
		break;
	case STATE_DISABLED:
		break;
	}

	// fill background
	pDC->DrawFullRect(pRect, crBk);

	// draw bottom line
	pDC->DrawHLine(pRect->x, pRect->x+pRect->cx-1, pRect->y+pRect->cy-3, crBottom1);
	pDC->DrawHLine(pRect->x, pRect->x+pRect->cx-1, pRect->y+pRect->cy-2, crBottom2);
	pDC->DrawHLine(pRect->x, pRect->x+pRect->cx-1, pRect->y+pRect->cy-1, crBottom3);

	// draw left line
	pDC->DrawLine(pRect->x, pRect->y+2, pRect->x, pRect->y+pRect->cy-5, crLeft);

	// draw rignt line
	pDC->DrawLine(pRect->x+pRect->cx-1, pRect->y+2, pRect->x+pRect->cx-1, pRect->y+pRect->cy-5, crRight);
}

void CWispDrawObj::DrawProgress(CWispDC* pDC, WISP_RECT* pRect, UINT uStyle, int nPrecent)
{
	int i;
	//
	// Frame
	//
	pDC->Draw3DRect(pRect, m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT	], m_crSystem[SC_CTRL_NORMAL_BORDER_BOTTOMRIGHT]);	  

	//pRect->DeflateRect(2, 2);
	pRect->x += 2;
	pRect->y += 2;
	pRect->cx -= 4;
	pRect->cy -= 4;

	CWispRect rcLine(*pRect);
	rcLine.cx = pRect->cx*nPrecent/1000;
	if(rcLine.cx>0)
	{
		for(i=0; i<6; i++)
		{
			if(rcLine.cy<=0)
				break;
			pDC->DrawHLine(rcLine.x, rcLine.x+rcLine.cx-1, rcLine.y, m_crSystem[SC_GRADIENT_GREEN_1+i]);
			pDC->DrawHLine(rcLine.x, rcLine.x+rcLine.cx-1, rcLine.y+rcLine.cy-1, m_crSystem[SC_GRADIENT_GREEN_1+i]);
			rcLine.DeflateRect(0, 1);
		}
		pDC->DrawFullRect(&rcLine,  m_crSystem[SC_GRADIENT_GREEN_7]);
		for(i=6; i<rcLine.cx; i+=7)
			pDC->DrawVLine(pRect->x+i, pRect->y, pRect->y+pRect->cy-1, m_crSystem[SC_CTRL_NORMAL_CLIENT_BG	]);
	}
}

void CWispDrawObj::DrawSystemStandardIcon(CWispDC* pDC,const WISP_RECT* pRect, UINT uStyle, UINT State)
{
	int nXOffset;
	int nYOffset;

	
	switch(uStyle)
	{
	case WISP_SSI_EXPANDBUTTON_COLLAPSE:
	case WISP_SSI_EXPANDBUTTON_EXPAND:
		{
			nXOffset = (pRect->cx-WISP_SSI_EXPANDBUTTON_SIZE)/2;
			nYOffset = (pRect->cy-WISP_SSI_EXPANDBUTTON_SIZE)/2;
			// »­¿ò
			WISP_RECT	rect;
			rect.x	= pRect->x+nXOffset;
			rect.y	= pRect->y+nYOffset;
			rect.cx	= WISP_SSI_EXPANDBUTTON_SIZE;
			rect.cy	= WISP_SSI_EXPANDBUTTON_SIZE;
			pDC->DrawRect(&rect, m_crSystem[SC_STDICON_NORMAL_BORDER	]);

			// »­¼Ó¼õºÅ
			nXOffset+=2;
			nYOffset+=2;
			pDC->DrawHLine(pRect->x+nXOffset, pRect->x+nXOffset+(WISP_SSI_EXPANDBUTTON_SIZE-4-1), pRect->y+nYOffset+(WISP_SSI_EXPANDBUTTON_SIZE-4)/2, m_crSystem[SC_STDICON_NORMAL_BORDER		]);
			if( uStyle==WISP_SSI_EXPANDBUTTON_COLLAPSE )
			{
				pDC->DrawVLine(pRect->x+nXOffset+(WISP_SSI_EXPANDBUTTON_SIZE-4)/2, pRect->y+nYOffset, pRect->y+nYOffset+(WISP_SSI_EXPANDBUTTON_SIZE-4-1), m_crSystem[SC_STDICON_NORMAL_BORDER		]);
			}
		}
		break;
	
	case WISP_SSI_REDIOBOX_UNSELECTED:
	case WISP_SSI_REDIOBOX_SELECTED:
	case WISP_SSI_REDIOBOX_SELECTED_DRAK:
	case WISP_SSI_REDIOBOX_UNSELECTED_DRAK:
		{
			pDC->DrawHLine(pRect->x+4,pRect->x+7,pRect->y,m_crSystem[SC_BLACK]);
			pDC->DrawHLine(pRect->x+4,pRect->x+7,pRect->y+11,m_crSystem[SC_BLACK]);
			pDC->DrawHLine(pRect->x+2,pRect->x+9,pRect->y+1,m_crSystem[SC_BLACK]);
			pDC->DrawHLine(pRect->x+2,pRect->x+9,pRect->y+10,m_crSystem[SC_BLACK]);

			pDC->DrawVLine(pRect->x,pRect->y+4,pRect->y+7,m_crSystem[SC_BLACK]);
			pDC->DrawVLine(pRect->x+11,pRect->y+4,pRect->y+7,m_crSystem[SC_BLACK]);
			pDC->DrawVLine(pRect->x+1,pRect->y+2,pRect->y+9,m_crSystem[SC_BLACK]);
			pDC->DrawVLine(pRect->x+10,pRect->y+2,pRect->y+9,m_crSystem[SC_BLACK]);
			pDC->DrawPixel(pRect->x+3,pRect->y+2,m_crSystem[SC_BLACK]);
			pDC->DrawPixel(pRect->x+8,pRect->y+2,m_crSystem[SC_BLACK]);
			pDC->DrawPixel(pRect->x+3,pRect->y+9,m_crSystem[SC_BLACK]);
			pDC->DrawPixel(pRect->x+8,pRect->y+9,m_crSystem[SC_BLACK]);

			pDC->DrawPixel(pRect->x+2,pRect->y+3,m_crSystem[SC_BLACK]);
			pDC->DrawPixel(pRect->x+2,pRect->y+8,m_crSystem[SC_BLACK]);
			pDC->DrawPixel(pRect->x+9,pRect->y+3,m_crSystem[SC_BLACK]);
			pDC->DrawPixel(pRect->x+9,pRect->y+8,m_crSystem[SC_BLACK]);

			pDC->DrawPixel(pRect->x+2,pRect->y+2,m_crSystem[SC_BLACK]);
			pDC->DrawPixel(pRect->x+9,pRect->y+2,m_crSystem[SC_BLACK]);
			pDC->DrawPixel(pRect->x+2,pRect->y+9,m_crSystem[SC_BLACK]);
			pDC->DrawPixel(pRect->x+9,pRect->y+9,m_crSystem[SC_BLACK]);

			if(uStyle==WISP_SSI_REDIOBOX_SELECTED||uStyle==WISP_SSI_REDIOBOX_SELECTED_DRAK)
			{			
				pDC->DrawVLine(pRect->x+5,pRect->y+4,pRect->y+7,m_crSystem[SC_BLACK]);
				pDC->DrawVLine(pRect->x+6,pRect->y+4,pRect->y+7,m_crSystem[SC_BLACK]);
				pDC->DrawHLine(pRect->x+4,pRect->x+7,pRect->y+5,m_crSystem[SC_BLACK]);
				pDC->DrawHLine(pRect->x+4,pRect->x+7,pRect->y+6,m_crSystem[SC_BLACK]);
			}
		};
	

		break;
	case WISP_SSI_CHECKBOX_UNCHECKED:
	case WISP_SSI_CHECKBOX_CHECKED:
	case WISP_SSI_CHECKBOX_SEMICHECKED:
	case WISP_SSI_CHECKBOX_CHECKMARK:
		{
			nXOffset = (pRect->cx-WISP_SSI_CHECKBOX_SIZE)/2;
			nYOffset = (pRect->cy-WISP_SSI_CHECKBOX_SIZE)/2;

			if(uStyle<=WISP_SSI_CHECKBOX_SEMICHECKED)
			{
				// »­¿ò
				WISP_RECT	rect;
				rect.x	= pRect->x+nXOffset;
				rect.y	= pRect->y+nYOffset;
				rect.cx	= WISP_SSI_CHECKBOX_SIZE;
				rect.cy	= WISP_SSI_CHECKBOX_SIZE;
				pDC->DrawRect(&rect,  m_crSystem[SC_STDICON_NORMAL_BORDER	]);
			}

			// semi selected, draw a small rectangle.
			if(uStyle==WISP_SSI_CHECKBOX_SEMICHECKED)
			{
				WISP_RECT	rect={pRect->x+nXOffset+3, pRect->y+nYOffset+3, WISP_SSI_CHECKBOX_SIZE-6, WISP_SSI_CHECKBOX_SIZE-6};
				pDC->DrawFullRect(&rect, m_crSystem[SC_STDICON_NORMAL_CHECKMARK	]);
			}

			// draw a check mark.
			if(uStyle==WISP_SSI_CHECKBOX_CHECKED || uStyle==WISP_SSI_CHECKBOX_CHECKMARK)
			{
				nXOffset = (pRect->cx-7)/2;
				nYOffset = (pRect->cy-7)/2;
				for(int i=0; i<3; i++)
				{
					pDC->DrawLine(pRect->x+nXOffset, pRect->y+nYOffset+2+i, pRect->x+nXOffset+2, pRect->y+nYOffset+4+i, m_crSystem[SC_STDICON_NORMAL_CHECKMARK	]);
					pDC->DrawLine(pRect->x+nXOffset+2, pRect->y+nYOffset+4+i, pRect->x+nXOffset+6, pRect->y+nYOffset+i, m_crSystem[SC_STDICON_NORMAL_CHECKMARK	]);
				}
			}
		}
		break;
	case WISP_SSI_VERT_INC_SPIN:
	case WISP_SSI_VERT_DEC_SPIN:
	case WISP_SSI_HORZ_INC_SPIN:
	case WISP_SSI_HORZ_DEC_SPIN:
		{
			CWispRect rc(*pRect);
			COLORREF crBkColor;
			switch(State)
			{
			case STATUS_NORMAL:
				crBkColor = m_crSystem[SC_SCROLL_NORMAL_BUTTON];
				break;
			case STATUS_HOVER:
				crBkColor = m_crSystem[SC_SCROLL_HOVER_BUTTON];
				break;
			case STATUS_DOWN:
				crBkColor = m_crSystem[SC_SCROLL_DOWN_BUTTON];
				break;
			}
			pDC->DrawRect(&rc, crBkColor);
			rc.DeflateRect(1, 1);
			pDC->DrawRect(&rc, m_crSystem[SC_WHITE]);
			rc.DeflateRect(1, 1);
			pDC->DrawFullRect(&rc, crBkColor);

			rc.DeflateRect(1, 2);
			int nHalf = rc.cy/2;
			switch(uStyle)
			{
			case WISP_SSI_HORZ_INC_SPIN:
				for(int i=-1; i<1; i++)
				{
					pDC->DrawLine(rc.x+rc.cx/4+i, rc.y+rc.cy/2-nHalf, rc.x+rc.cx/4+nHalf+i, rc.y+rc.cy/2, m_crSystem[SC_BLUE]);
					pDC->DrawLine(rc.x+rc.cx/4+i, rc.y+rc.cy/2+nHalf, rc.x+rc.cx/4+nHalf+i, rc.y+rc.cy/2, m_crSystem[SC_BLUE]);
				}
				for(int i=2; i<4; i++)
				{
					pDC->DrawLine(rc.x+rc.cx/4+i, rc.y+rc.cy/2-nHalf, rc.x+rc.cx/4+nHalf+i, rc.y+rc.cy/2, m_crSystem[SC_BLUE]);
					pDC->DrawLine(rc.x+rc.cx/4+i, rc.y+rc.cy/2+nHalf, rc.x+rc.cx/4+nHalf+i, rc.y+rc.cy/2, m_crSystem[SC_BLUE]);
				}
				break;
			case WISP_SSI_HORZ_DEC_SPIN:
				for(int i=-1; i<1; i++)
				{
					pDC->DrawLine(rc.x2()-rc.cx/4-i, rc.y+rc.cy/2-nHalf, rc.x2()-rc.cx/4-nHalf-i, rc.y+rc.cy/2, m_crSystem[SC_BLUE]);
					pDC->DrawLine(rc.x2()-rc.cx/4-i, rc.y+rc.cy/2+nHalf, rc.x2()-rc.cx/4-nHalf-i, rc.y+rc.cy/2, m_crSystem[SC_BLUE]);
				}
				for(int i=2; i<4; i++)
				{
					pDC->DrawLine(rc.x2()-rc.cx/4-i, rc.y+rc.cy/2-nHalf, rc.x2()-rc.cx/4-nHalf-i, rc.y+rc.cy/2, m_crSystem[SC_BLUE]);
					pDC->DrawLine(rc.x2()-rc.cx/4-i, rc.y+rc.cy/2+nHalf, rc.x2()-rc.cx/4-nHalf-i, rc.y+rc.cy/2, m_crSystem[SC_BLUE]);
				}
				break;
			case WISP_SSI_VERT_INC_SPIN:
				for(int i=-1; i<1; i++)
				{
					pDC->DrawLine(rc.x+rc.cx/2-nHalf, rc.y+rc.cy/4+i, rc.x+rc.cx/2, rc.y+rc.cy/4+nHalf+i, m_crSystem[SC_BLUE]);
					pDC->DrawLine(rc.x+rc.cx/2+nHalf, rc.y+rc.cy/4+i, rc.x+rc.cx/2, rc.y+rc.cy/4+nHalf+i, m_crSystem[SC_BLUE]);
				}
				for(int i=2; i<4; i++)
				{
					pDC->DrawLine(rc.x+rc.cx/2-nHalf, rc.y+rc.cy/4+i, rc.x+rc.cx/2, rc.y+rc.cy/4+nHalf+i, m_crSystem[SC_BLUE]);
					pDC->DrawLine(rc.x+rc.cx/2+nHalf, rc.y+rc.cy/4+i, rc.x+rc.cx/2, rc.y+rc.cy/4+nHalf+i, m_crSystem[SC_BLUE]);
				}
				break;
			case WISP_SSI_VERT_DEC_SPIN:
				for(int i=-1; i<1; i++)
				{
					pDC->DrawLine(rc.x+rc.cx/2-nHalf, rc.y2()-rc.cy/4-i, rc.x+rc.cx/2, rc.y2()-rc.cy/4-nHalf-i, m_crSystem[SC_BLUE]);
					pDC->DrawLine(rc.x+rc.cx/2+nHalf, rc.y2()-rc.cy/4-i, rc.x+rc.cx/2, rc.y2()-rc.cy/4-nHalf-i, m_crSystem[SC_BLUE]);
				}
				for(int i=2; i<4; i++)
				{													  
					pDC->DrawLine(rc.x+rc.cx/2-nHalf, rc.y2()-rc.cy/4-i, rc.x+rc.cx/2, rc.y2()-rc.cy/4-nHalf-i, m_crSystem[SC_BLUE]);
					pDC->DrawLine(rc.x+rc.cx/2+nHalf, rc.y2()-rc.cy/4-i, rc.x+rc.cx/2, rc.y2()-rc.cy/4-nHalf-i, m_crSystem[SC_BLUE]);
				}
				break;
			}
		}
		break;
	case WISP_SSI_CLOSE:
	case WISP_SSI_MAXIMIZE:
	case WISP_SSI_RESTORE:
	case WISP_SSI_MINIMIZE:
		{
			COLORREF color;
			switch(State)
			{
			case STATUS_NORMAL:	// caption bar using dark color, so use DOWN color as NORMAL color.
				color =  m_crSystem[SC_STDICON_DOWN_BORDER];
				break;
			case STATUS_HOVER:
				color =  m_crSystem[SC_STDICON_HOVER_BORDER	];
				break;
			case STATUS_DOWN:
				color =  m_crSystem[SC_STDICON_NORMAL_BORDER	];
				break;
			}

			CWispRect rc(pRect);
			// Border
			pDC->DrawRoundRect(&rc, color);
			//rc.DeflateRect(1, 1);
			//pDC->DrawRect(&rc, color);

			rc.DeflateRect(4, 4);
			if(uStyle==WISP_SSI_CLOSE)
			{
				// cross
				pDC->DrawLine(rc.x+1,	rc.y,		rc.x2(),	rc.y2()-1,	color);
				pDC->DrawLine(rc.x+1,	rc.y+1,		rc.x2()-1,	rc.y2()-1,	color);
				pDC->DrawLine(rc.x,		rc.y+1,		rc.x2()-1,	rc.y2(),	color);
				pDC->DrawLine(rc.x,		rc.y2()-1,	rc.x2()-1,	rc.y,		color);
				pDC->DrawLine(rc.x+1,	rc.y2()-1,	rc.x2()-1,	rc.y+1,		color);
				pDC->DrawLine(rc.x+1,	rc.y2(),	rc.x2(),	rc.y+1,		color);
			}
			else if(uStyle==WISP_SSI_MINIMIZE)
			{
				// short line
				pDC->DrawLine(rc.x,	rc.y2()-2,	rc.x2(),	rc.y2()-2,	color);
				pDC->DrawLine(rc.x,	rc.y2()-1,	rc.x2(),	rc.y2()-1,	color);
				pDC->DrawLine(rc.x,	rc.y2(),	rc.x2(),	rc.y2(),	color);
			}
			else if(uStyle==WISP_SSI_MAXIMIZE)
			{
				// small rect
				pDC->DrawRect(&rc, color);
				pDC->DrawLine(rc.x+1, rc.y+1, rc.x2()-1, rc.y+1, color);
				pDC->DrawLine(rc.x+1, rc.y+2, rc.x2()-1, rc.y+2, color);
			}
			else if(uStyle==WISP_SSI_RESTORE)
			{
				rc.DeflateRect(1, 1);
				rc.OffsetRect(1, -1);
				pDC->DrawRect(&rc, color);
				pDC->DrawLine(rc.x+1, rc.y+1, rc.x2()-1, rc.y+1, color);
	//			pDC->DrawLine(rc.x+1, rc.y+2, rc.x2()-1, rc.y+2, color);

				rc.OffsetRect(-3, 4);
				rc.cy --;
				pDC->DrawRect(&rc, color);
				pDC->DrawLine(rc.x+1, rc.y+1, rc.x2()-1, rc.y+1, color);
	//			pDC->DrawLine(rc.x+1, rc.y+2, rc.x2()-1, rc.y+2, color);
			}
		}
		break;
	}
}

void CWispDrawObj::DrawCursor(WISP_POINT* pHotPT, CWispDC* pClipDC,UINT CursorType,CWispDIB*pDIB)
{
	switch(CursorType)
	{
	case WISP_CT_ARROW:
		DrawCursorArrow(pClipDC,pHotPT);
		break;
	case WISP_CT_DRAG_ARROW:
		DrawCursorDrag(pClipDC,pHotPT);
		break;
	case WISP_CT_RESIZE_VERT:
		DrawCursorResizeVert(pClipDC,pHotPT);
		break;
	case WISP_CT_RESIZE_HORZ:
		DrawCursorResizeHorz(pClipDC,pHotPT);
		break;
	case WISP_CT_RESIZE_LEFT_LEAN:
		DrawCursorResizeLeftLean(pClipDC,pHotPT);
		break;
	case WISP_CT_RESIZE_RIGHT_LEAN:
		DrawCursorResizeRightLean(pClipDC,pHotPT);
		break;
	default:
		if(pDIB)
			pClipDC->DrawDIB(pHotPT->x,pHotPT->y,pDIB);
		else
			DrawCursorArrow(pClipDC,pHotPT);
		break;
	}
}


void CWispDrawObj::DrawCursorArrow(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	int x1,y1,x2,y2;
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT.x = 0;
		gpCurWisp->m_MouseHotPT.y = 0;
		gpCurWisp->m_MouseSize.cx = 16;
		gpCurWisp->m_MouseSize.cy = 16;
		return;
	}
	x1 = pHotPT->x;
	y1 = pHotPT->y;
	x2 = pHotPT->x;
	y2 = pHotPT->y+15;
	for(int i=0; i<3; i++)
	{
		int a1 = x1, b1=y1, a2=x2, b2=y2;
			pClipDC->DrawVLine(a1, b1, b2, m_crSystem[SC_GRADIENT_GREEN_7-2*i]);
		x1+=1;
		y1+=1;
		x2+=1;
		y2-=1;
	}

	x1 = pHotPT->x;
	y1 = pHotPT->y;
	x2 = pHotPT->x+15;
	y2 = pHotPT->y+15;
	for(int i=0; i<4; i++)
	{
		int a1 = x1, b1=y1, a2=x2, b2=y2;
			pClipDC->DrawLine(a1, b1, a2, b2, m_crSystem[SC_GRADIENT_GREEN_7-2*i]);
		x1+=1;
		y1+=2;
		x2-=2;
		y2-=1;
	}

	x1 = pHotPT->x+15;
	y1 = pHotPT->y+15;
	x2 = pHotPT->x+2;
	y2 = pHotPT->y+11;
	for(int i=0; i<1; i++)
	{
		pClipDC->DrawLine(x1, y1, x2, y2, m_crSystem[SC_GRADIENT_GREEN_7-i]);
		//x1+=1;
		y1-=1;
		x2-=1;
		y2-=1;
	}
}
void CWispDrawObj::DrawCursorDrag(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	return;
	int x1,y1,x2,y2;
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT.x = 0;
		gpCurWisp->m_MouseHotPT.y = 0;
		gpCurWisp->m_MouseSize.cx = 16;
		gpCurWisp->m_MouseSize.cy = 16;
		return;
	}
	x1 = pHotPT->x;
	y1 = pHotPT->y;
	x2 = pHotPT->x;
	y2 = pHotPT->y+15;
	for(int i=0; i<3; i++)
	{
		int a1 = x1, b1=y1, a2=x2, b2=y2;
		pClipDC->DrawVLine(a1, b1, b2, m_crSystem[SC_GRADIENT_GREEN_7-2*i]);
		x1+=1;
		y1+=1;
		x2+=1;
		y2-=1;
	}

	x1 = pHotPT->x;
	y1 = pHotPT->y;
	x2 = pHotPT->x+15;
	y2 = pHotPT->y+15;
	for(int i=0; i<4; i++)
	{
		int a1 = x1, b1=y1, a2=x2, b2=y2;
		pClipDC->DrawLine(a1, b1, a2, b2, m_crSystem[SC_GRADIENT_GREEN_7-2*i]);
		x1+=1;
		y1+=2;
		x2-=2;
		y2-=1;
	}

	x1 = pHotPT->x+15;
	y1 = pHotPT->y+15;
	x2 = pHotPT->x+2;
	y2 = pHotPT->y+11;
	for(int i=0; i<1; i++)
	{
		pClipDC->DrawLine(x1, y1, x2, y2, m_crSystem[SC_GRADIENT_GREEN_7-i]);
		//x1+=1;
		y1-=1;
		x2-=1;
		y2-=1;
	}
}
void CWispDrawObj::DrawCursorResizeVert(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT.x = 6;
		gpCurWisp->m_MouseHotPT.y = 7;
		gpCurWisp->m_MouseSize.cx = 13;
		gpCurWisp->m_MouseSize.cy = 15;
		return;
	}
	pClipDC->DrawLine(pHotPT->x-2,pHotPT->y-4, pHotPT->x, pHotPT->y-6, m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x-2,pHotPT->y-5, pHotPT->x, pHotPT->y-7, m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawLine(pHotPT->x+2,pHotPT->y-4, pHotPT->x, pHotPT->y-6, m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x+2,pHotPT->y-5, pHotPT->x, pHotPT->y-7, m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawVLine(pHotPT->x-1,pHotPT->y-6, pHotPT->y+6, m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawVLine(pHotPT->x,  pHotPT->y-7,pHotPT->y+7,m_crSystem[SC_GRADIENT_GREEN_2]);
	pClipDC->DrawVLine(pHotPT->x+1,pHotPT->y-6, pHotPT->y+6, m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawLine(pHotPT->x-2,pHotPT->y+4, pHotPT->x, pHotPT->y+6, m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x-2,pHotPT->y+5, pHotPT->x, pHotPT->y+7, m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawLine(pHotPT->x+2,pHotPT->y+4, pHotPT->x, pHotPT->y+6, m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x+2,pHotPT->y+5, pHotPT->x, pHotPT->y+7, m_crSystem[SC_GRADIENT_GREEN_5]);
}

void CWispDrawObj::DrawCursorResizeHorz(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT.x = 7;
		gpCurWisp->m_MouseHotPT.y = 6;
		gpCurWisp->m_MouseSize.cx = 15;
		gpCurWisp->m_MouseSize.cy = 13;
		return;
	}
	pClipDC->DrawLine(pHotPT->x-4,pHotPT->y-2,pHotPT->x-6,pHotPT->y, m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x-5,pHotPT->y-2,pHotPT->x-7,pHotPT->y,m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawLine(pHotPT->x-4,pHotPT->y+2,pHotPT->x-6,pHotPT->y, m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x-5,pHotPT->y+2,pHotPT->x-7,pHotPT->y,m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawHLine(pHotPT->x-6,pHotPT->x+6,pHotPT->y-1,m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawHLine(pHotPT->x-7,pHotPT->x+7,pHotPT->y  ,m_crSystem[SC_GRADIENT_GREEN_2]);
	pClipDC->DrawHLine(pHotPT->x+6,pHotPT->x-6,pHotPT->y+1,m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawLine(pHotPT->x+4,pHotPT->y-2,pHotPT->x+6,pHotPT->y,m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x+5,pHotPT->y-2,pHotPT->x+7,pHotPT->y,m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawLine(pHotPT->x+4,pHotPT->y+2,pHotPT->x+6,pHotPT->y,m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x+5,pHotPT->y+2,pHotPT->x+7,pHotPT->y,m_crSystem[SC_GRADIENT_GREEN_5]);
}

void CWispDrawObj::DrawCursorResizeLeftLean(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT.x = 6;
		gpCurWisp->m_MouseHotPT.y = 6;
		gpCurWisp->m_MouseSize.cx = 11;
		gpCurWisp->m_MouseSize.cy = 11;
		return;
	}
	pClipDC->DrawLine(pHotPT->x-5,pHotPT->y-5,pHotPT->x-5,pHotPT->y  ,m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x-5,pHotPT->y-5,pHotPT->x  ,pHotPT->y-5,m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawLine(pHotPT->x-3,pHotPT->y-4,pHotPT->x+4,pHotPT->y+3,m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x-4,pHotPT->y-4,pHotPT->x+4,pHotPT->y+4,m_crSystem[SC_GRADIENT_GREEN_2]);
	pClipDC->DrawLine(pHotPT->x-4,pHotPT->y-3,pHotPT->x+3,pHotPT->y+4,m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawLine(pHotPT->x  ,pHotPT->y+5,pHotPT->x+5,pHotPT->y+5,m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x+5,pHotPT->y  ,pHotPT->x+5,pHotPT->y+5,m_crSystem[SC_GRADIENT_GREEN_5]);
}

void CWispDrawObj::DrawCursorResizeRightLean(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT.x = 6;
		gpCurWisp->m_MouseHotPT.y = 6;
		gpCurWisp->m_MouseSize.cx = 11;
		gpCurWisp->m_MouseSize.cy = 11;
		return;
	}
	pClipDC->DrawLine(pHotPT->x  ,pHotPT->y-5,pHotPT->x+5,pHotPT->y-5,m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x+5,pHotPT->y  ,pHotPT->x+5,pHotPT->y-5,m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawLine(pHotPT->x-3,pHotPT->y+4,pHotPT->x+4,pHotPT->y-3,m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x-4,pHotPT->y+4,pHotPT->x+4,pHotPT->y-4,m_crSystem[SC_GRADIENT_GREEN_2]);
	pClipDC->DrawLine(pHotPT->x-4,pHotPT->y+3,pHotPT->x+3,pHotPT->y-4,m_crSystem[SC_GRADIENT_GREEN_5]);

	pClipDC->DrawLine(pHotPT->x-5,pHotPT->y  ,pHotPT->x-5,pHotPT->y+5,m_crSystem[SC_GRADIENT_GREEN_5]);
	pClipDC->DrawLine(pHotPT->x  ,pHotPT->y+5,pHotPT->x-5,pHotPT->y+5,m_crSystem[SC_GRADIENT_GREEN_5]);
}

void CWispDrawObj::DrawListColumnTitleBK(CWispDC* pClipDC,WISP_RECT*pRc)
{
	DrawToolbarBK(pClipDC,pRc);
}


void CWispDrawObj::DrawListSelectedItemBK(CWispDC* pClipDC,WISP_RECT*pRc)
{
	pClipDC->DrawFullRect(pRc,m_crSystem[SC_CTRL_SELECTED_BG]);
}


void CWispDrawObj::DrawMenuIconSpaceBK(CWispDC* pClipDC,WISP_RECT*pRc)
{
	pClipDC->DrawFullRect(pRc,m_crSystem[SC_MENU_BG]);
}

void CWispDrawObj::DrawMenuBK(CWispDC*pClipDC,WISP_RECT*pRc,UINT Status)
{	
	if(Status==STATUS_HOVER)
		pClipDC->DrawFullRect(pRc,m_crSystem[SC_CTRL_HOVER_BG]);
	else
		pClipDC->DrawFullRect(pRc,m_crSystem[SC_MENU_BG]);
}

void CWispDrawObj::DrawMenuString(CWispDC*pClipDC,WISP_RECT*pRc,WISP_PCSTR String,UINT Status)
{
	pClipDC->DrawShadowString(pRc,String);
}


void CWispDrawObj::DrawMenuTopFrame(CWispDC* pClipDC,WISP_RECT*pRc)
{
	DrawMenuIconSpaceBK(pClipDC,pRc);
}

void CWispDrawObj::DrawMenuBottomFrame(CWispDC* pClipDC,WISP_RECT*pRc)
{
	DrawMenuIconSpaceBK(pClipDC,pRc);	
}

CWispDIBDrawObj::CWispDIBDrawObj()
{
	m_szSkinDir = "\\Skin\\Default";
}

CWispDIBDrawObj::~CWispDIBDrawObj()
{
}

bool CWispDIBDrawObj::Init()
{
	char szBuffer[MAX_FN_LEN];
	TStrCpy(szBuffer,m_szSkinDir);
	TStrCat(szBuffer,"\\VertInc.bmp");
	m_DIBVertIncSpin.Load(szBuffer,16,16,4);
	TStrCpy(szBuffer,m_szSkinDir);
	TStrCat(szBuffer,"\\VertDec.bmp");
	m_DIBVertDecSpin.Load(szBuffer,16,16,4);
	TStrCpy(szBuffer,m_szSkinDir);
	TStrCat(szBuffer,"\\HorzInc.bmp");
	m_DIBHorzIncSpin.Load(szBuffer,16,16,4);
	TStrCpy(szBuffer,m_szSkinDir);
	TStrCat(szBuffer,"\\HorzDec.bmp");
	m_DIBHorzDecSpin.Load(szBuffer,16,16,4);
	TStrCpy(szBuffer,m_szSkinDir);
	TStrCat(szBuffer,"\\Min.bmp");
	m_DIBMin.Load(szBuffer,16,16,4);
	TStrCpy(szBuffer,m_szSkinDir);
	TStrCat(szBuffer,"\\Max.bmp");
	m_DIBMax.Load(szBuffer,16,16,4);
	TStrCpy(szBuffer,m_szSkinDir);
	TStrCat(szBuffer,"\\Normal.bmp");
	m_DIBRestore.Load(szBuffer,16,16,4);
	TStrCpy(szBuffer,m_szSkinDir);
	TStrCat(szBuffer,"\\Close.bmp");
	m_DIBClose.Load(szBuffer,16,16,4);
	TStrCpy(szBuffer,m_szSkinDir);
	TStrCat(szBuffer,"\\RedioBox.bmp");
	m_DIBRedioBoxIcon.Load(szBuffer,13,13,6);
	m_DIBRedioBoxIcon.SetType(WISP_DIB_TK);

	m_DIBArrow.Load("\\Cursor\\Arrow.bmp");
	m_DIBArrow.SetType(WISP_DIB_TK);

	m_DIBDrag.Load("\\Cursor\\Drag.bmp");
	m_DIBDrag.SetType(WISP_DIB_TK);
	m_DIBDrag.SetHotPoint(m_DIBDrag.m_FrameBuffer.Width/2,m_DIBDrag.m_FrameBuffer.Height/2);

	m_DIBHResize.Load("\\Cursor\\HResize.bmp");
	m_DIBHResize.SetType(WISP_DIB_TK);
	m_DIBHResize.SetHotPoint(m_DIBHResize.m_FrameBuffer.Width/2,m_DIBHResize.m_FrameBuffer.Height/2);

	m_DIBVResize.Load("\\Cursor\\VResize.bmp");
	m_DIBVResize.SetType(WISP_DIB_TK);
	m_DIBVResize.SetHotPoint(m_DIBVResize.m_FrameBuffer.Width/2,m_DIBVResize.m_FrameBuffer.Height/2);

	m_DIBLResize.Load("\\Cursor\\LResize.bmp");
	m_DIBLResize.SetType(WISP_DIB_TK);
	m_DIBLResize.SetHotPoint(m_DIBLResize.m_FrameBuffer.Width/2,m_DIBLResize.m_FrameBuffer.Height/2);

	m_DIBRResize.Load("\\Cursor\\RResize.bmp");
	m_DIBRResize.SetType(WISP_DIB_TK);
	m_DIBRResize.SetHotPoint(m_DIBRResize.m_FrameBuffer.Width/2,m_DIBRResize.m_FrameBuffer.Height/2);

	gpCurWisp->m_MouseHotPT = m_DIBArrow.m_HotPT;
	gpCurWisp->m_MouseSize.cx = m_DIBArrow.m_FrameBuffer.Width;
	gpCurWisp->m_MouseSize.cy = m_DIBArrow.m_FrameBuffer.Height;
	return true;
}

void CWispDIBDrawObj::Release()
{
	m_DIBVertIncSpin.Destroy();
	m_DIBVertDecSpin.Destroy();
	m_DIBHorzIncSpin.Destroy();
	m_DIBHorzDecSpin.Destroy();
	m_DIBMin.Destroy();
	m_DIBMax.Destroy();
	m_DIBRestore.Destroy();
	m_DIBClose.Destroy();
	m_DIBArrow.Destroy();
	m_DIBRedioBoxIcon.Destroy();
	m_DIBHResize.Destroy();
	m_DIBVResize.Destroy();
	m_DIBLResize.Destroy();
	m_DIBRResize.Destroy();
}

void CWispDIBDrawObj::DrawBorder(CWispDC*pDC,WISP_RECT*pRect,int Size)
{
	COLORREF Color;
	CWispWnd*pWnd=(CWispWnd*)pDC->m_pWispWnd;
	for(int l=Size-1;l>=0;l--)
	{
		Color=GRAY_CHG(m_crSystem[SC_BORDER_BG],3,Size-l+1);
		pDC->DrawVLine(pRect->x+l,pRect->y+l,pRect->y+pRect->cy-1-l,Color);
		pDC->DrawVLine(pRect->x+pRect->cx-1-l,pRect->y+l,pRect->y+pRect->cy-1-l,Color);
		Color=GRAY_CHG(m_crSystem[SC_BORDER_BG],3,Size-l+1);
		pDC->DrawHLine(pRect->x+l,pRect->x+pRect->cx-1-l,pRect->y+l,Color);
		pDC->DrawHLine(pRect->x+l,pRect->x+pRect->cx-1-l,pRect->y+pRect->cy-1-l,Color);
	}
}

void CWispDIBDrawObj::DrawCaption(CWispDC*pDC,WISP_RECT*pRect)
{
	pDC->DrawMiddleYGrayChgFullRect(m_crSystem[SC_CAPTION_BG],m_crSystem[SC_CAPTION_LIGHT_BG],pRect);
}

void CWispDIBDrawObj::DrawToolbarBK(CWispDC*pDC,WISP_RECT*pRect)
{
	pDC->DrawMiddleYGrayChgFullRect(WISP_RGB(172,214,255),WISP_RGB(62,158,255),pRect);
}

void CWispDIBDrawObj::DrawSystemStandardIcon(CWispDC* pDC,const WISP_RECT* pRect, UINT uStyle, UINT State)
{
	switch(uStyle)
	{
	case WISP_SSI_VERT_INC_SPIN:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBVertIncSpin.GetDIB(State));
		break;
	case WISP_SSI_VERT_DEC_SPIN:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBVertDecSpin.GetDIB(State));
		break;
	case WISP_SSI_HORZ_INC_SPIN:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBHorzIncSpin.GetDIB(State));
		break;
	case WISP_SSI_HORZ_DEC_SPIN:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBHorzDecSpin.GetDIB(State));
		break;
	case WISP_SSI_MAXIMIZE:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBMax.GetDIB(State));
		break;
	case WISP_SSI_MINIMIZE:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBMin.GetDIB(State));
		break;
	case WISP_SSI_RESTORE:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBRestore.GetDIB(State));
		break;
	case WISP_SSI_CLOSE:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBClose.GetDIB(State));
		break;
	case WISP_SSI_REDIOBOX_UNSELECTED:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBRedioBoxIcon.GetDIB(0));
		break;
	case WISP_SSI_REDIOBOX_UNSELECTED_DRAK:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBRedioBoxIcon.GetDIB(2));
		break;
	case WISP_SSI_REDIOBOX_SELECTED:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBRedioBoxIcon.GetDIB(3));
		break;
	case WISP_SSI_REDIOBOX_SELECTED_DRAK:
		pDC->DrawDIB(pRect->x,pRect->y,m_DIBRedioBoxIcon.GetDIB(5));
		break;
	default:
		CWispDrawObj::DrawSystemStandardIcon(pDC,pRect,uStyle,State);
		break;
	}
}

void CWispDIBDrawObj::DrawCursorArrow(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT = m_DIBArrow.m_HotPT;
		gpCurWisp->m_MouseSize.cx = m_DIBArrow.m_FrameBuffer.Width;
		gpCurWisp->m_MouseSize.cy = m_DIBArrow.m_FrameBuffer.Height;
		return;
	}
	pClipDC->DrawDIB(pHotPT->x,pHotPT->y,&m_DIBArrow);
}
void CWispDIBDrawObj::DrawCursorDrag(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT = m_DIBDrag.m_HotPT;
		gpCurWisp->m_MouseSize.cx = m_DIBDrag.m_FrameBuffer.Width;
		gpCurWisp->m_MouseSize.cy = m_DIBDrag.m_FrameBuffer.Height;
		return;
	}
	pClipDC->DrawDIB(pHotPT->x,pHotPT->y,&m_DIBDrag);
}
void CWispDIBDrawObj::DrawCursorResizeVert(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT = m_DIBVResize.m_HotPT;
		gpCurWisp->m_MouseSize.cx = m_DIBVResize.m_FrameBuffer.Width;
		gpCurWisp->m_MouseSize.cy = m_DIBVResize.m_FrameBuffer.Height;
		return;
	}
	pClipDC->DrawDIB(pHotPT->x,pHotPT->y,&m_DIBVResize);
}

void CWispDIBDrawObj::DrawCursorResizeHorz(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT = m_DIBHResize.m_HotPT;
		gpCurWisp->m_MouseSize.cx = m_DIBHResize.m_FrameBuffer.Width;
		gpCurWisp->m_MouseSize.cy = m_DIBHResize.m_FrameBuffer.Height;
		return;
	}
	pClipDC->DrawDIB(pHotPT->x,pHotPT->y,&m_DIBHResize);
}

void CWispDIBDrawObj::DrawCursorResizeLeftLean(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT = m_DIBLResize.m_HotPT;
		gpCurWisp->m_MouseSize.cx = m_DIBLResize.m_FrameBuffer.Width;
		gpCurWisp->m_MouseSize.cy = m_DIBLResize.m_FrameBuffer.Height;
		return;
	}
	pClipDC->DrawDIB(pHotPT->x,pHotPT->y,&m_DIBLResize);
}

void CWispDIBDrawObj::DrawCursorResizeRightLean(CWispDC* pClipDC,WISP_POINT* pHotPT)
{
	if(pClipDC==NULL)
	{
		gpCurWisp->m_MouseHotPT = m_DIBRResize.m_HotPT;
		gpCurWisp->m_MouseSize.cx = m_DIBRResize.m_FrameBuffer.Width;
		gpCurWisp->m_MouseSize.cy = m_DIBRResize.m_FrameBuffer.Height;
		return;
	}
	pClipDC->DrawDIB(pHotPT->x,pHotPT->y,&m_DIBRResize);	
}

void CWispDIBDrawObj::DrawSplitRect(CWispDC*pDC,WISP_RECT*pRect,bool bHorz)
{
	CWispWnd*pWnd=(CWispWnd*)pDC->m_pWispWnd;
	if(bHorz)
	{		
		pDC->DrawXGrayChgFullRect(pRect,m_crSystem[SC_BORDER_BG],4);
	}
	else
	{
		pDC->DrawYGrayChgFullRect(pRect,m_crSystem[SC_BORDER_BG],4);
	}	
}

void CWispDIBDrawObj::DrawVertScrollSlideRect(CWispDC*pDC,WISP_RECT*pRect)
{
	CWispRect rc(pRect);
	pDC->DrawRoundRect(&rc, m_crSystem[SC_SCROLL_NORMAL_BUTTON]);
	rc.DeflateRect(1, 1);
	pDC->DrawRect(&rc, m_crSystem[SC_WHITE]);
	rc.DeflateRect(1, 1);
	pDC->DrawMiddleXGrayChgFullRect(m_crSystem[SC_SCROLL_SLIDE_DARK_BG],m_crSystem[SC_SCROLL_SLIDE_BG],&rc);
	if(rc.cy>=10)
	{
		for(int i=0; i<8; i+=2)
		{
			pDC->DrawHLine( rc.x+2, rc.x2()-2, (rc.cy-8)/2+rc.y+i, m_crSystem[SC_LIGHT_GRAY]);
			pDC->DrawHLine( rc.x+2, rc.x2()-2, (rc.cy-8)/2+rc.y+i+1,  m_crSystem[SC_GRAY]);
		}
	}
}

void CWispDIBDrawObj::DrawHorzScrollSlideRect(CWispDC*pDC,WISP_RECT*pRect)
{
	CWispRect rc(pRect);
	pDC->DrawRoundRect(&rc, m_crSystem[SC_SCROLL_NORMAL_BUTTON]);
	rc.DeflateRect(1, 1);
	pDC->DrawRect(&rc, m_crSystem[SC_WHITE]);
	rc.DeflateRect(1, 1);
	pDC->DrawMiddleYGrayChgFullRect(m_crSystem[SC_SCROLL_SLIDE_DARK_BG],m_crSystem[SC_SCROLL_SLIDE_BG],&rc);
	if(rc.cx>=10)
	{
		for(int i=0; i<8; i+=2)
		{
			pDC->DrawVLine( (rc.cx-8)/2+rc.x+i, rc.y+2, rc.y2()-2,  m_crSystem[SC_LIGHT_GRAY]);
			pDC->DrawVLine( (rc.cx-8)/2+rc.x+i+1, rc.y+2, rc.y2()-2,  m_crSystem[SC_GRAY]);
		}
	}
}

void CWispDIBDrawObj::DrawListColumnTitleBK(CWispDC* pClipDC,WISP_RECT*pRc)
{
	DrawToolbarBK(pClipDC,pRc);
}

void CWispDIBDrawObj::DrawListSelectedItemBK(CWispDC* pClipDC,WISP_RECT*pRc)
{
	pClipDC->DrawMiddleYGrayChgFullRect(m_crSystem[SC_CTRL_SELECTED_BG],m_crSystem[SC_CTRL_SELECTED_LIGHT_BG],pRc);
}

void CWispDIBDrawObj::DrawMenuIconSpaceBK(CWispDC* pClipDC,WISP_RECT*pRc)
{
	CWispDrawObj::DrawMenuIconSpaceBK(pClipDC,pRc);
}

void CWispDIBDrawObj::DrawMenuBK(CWispDC* pClipDC,WISP_RECT*pRc,UINT Status)
{
	if(Status==STATUS_HOVER)
		pClipDC->DrawMiddleYGrayChgFullRect(m_crSystem[SC_CTRL_HOVER_BG],m_crSystem[SC_CTRL_HOVER_LIGHT_BG],pRc);
	else
		pClipDC->DrawMiddleYGrayChgFullRect(m_crSystem[SC_MENU_BG],m_crSystem[SC_MENU_LIGHT_BG],pRc);
}

void CWispDIBDrawObj::DrawMenuString(CWispDC*pClipDC,WISP_RECT*pRc,WISP_PCSTR String,UINT Status)
{
	if(Status==STATE_DISABLED)
	{
		pClipDC->SetTextColor(m_crSystem[SC_LIGHT_GRAY]);
		pClipDC->SetShadowTextColor(m_crSystem[SC_SHADOW_LIGHT]);
		pClipDC->DrawShadowString(pRc,String);
		pClipDC->RestoreTextColor();
		pClipDC->RestoreShadowTextColor();
	}
	else
	{
		pClipDC->DrawShadowString(pRc,String);
	}
}
