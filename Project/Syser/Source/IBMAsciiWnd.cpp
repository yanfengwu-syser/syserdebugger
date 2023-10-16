#include "stdafx.h"
#include "IBMAsciiWnd.h"
WISP_MSG_MAP_BEGIN(CIBMAsciiWnd)

WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispForm)
CIBMAsciiWnd::CIBMAsciiWnd()
{
	m_pFormRes = m_FormRes;	
	m_FontType=2;
}
CIBMAsciiWnd::~CIBMAsciiWnd()
{

}
bool CIBMAsciiWnd::OnFormCreate(IN WISP_MSG*pMsg)
{	
	SetBGColor(ColorOption.clrSDBK);	
	return true;
}
void CIBMAsciiWnd::DrawIndex(int x,int y)
{
	WCHAR pString[64];
	WCHAR pString2[10];
	int i;
	m_ClientDC.SetTextColor(WISP_RGB(0,0,0xff));
	for(i=0;i<16;i++)  
	{
		pString[i*2]='0'+i;
		pString2[0]='0'+i;
		pString2[1]='0';
		pString[i*2+1]=' ';
		if(i>9)
		{
			pString[i*2]='A'+i-10;
			pString2[0]='A'+i-10;
		}
		TSPrintf(pString2,WSTR("%02X(%-3d)"),i*16,i*16);
		m_ClientDC.DrawString(0,y+32+i*32,pString2,7,0,1);//每行的纵向索引
	}
	m_ClientDC.DrawString(x,y,pString,32,0,1);//第1行横向索引
	int n=0;
	for(i=0;i<16;i++)
	{
		pString[i*2]='0'+i;
		pString[i*2+1]=' ';
		if(i>9)
		{
			pString[i*2]='1';
			pString[i*2+1]='0'+i-10;
		}
	}
	m_ClientDC.DrawString(x,y+32+i*32,pString,20,0,1);  //最后一行的横向索引
	m_ClientDC.DrawString(x+12*20-8,y+32+i*32,&pString[20],12,0,1);
	
}
void CIBMAsciiWnd::DrawGrid(int x,int y,int cx,int cy)
{
	WCHAR pString[64];
	WCHAR pString2[64];
	int i,j;
	m_ClientDC.SetTextColor(WISP_RGB(0,0,0xff));
	pString[0]=0xda;
	for(i=0;i<16;i++)
	{
		pString[i*2+1]=0xc4;
		pString[i*2+2]=0xc2;
	}
	pString[32]=0xbf;
	m_ClientDC.DrawString(x,y,pString,33,0,1);
	for(i=0;i<16;i++)
	{
		pString[0]=0xb3;
		pString2[0]=0xc3;
		for(j=0;j<15;j++)
		{
			pString[j*2+1]=0x20;
			pString[j*2+1+1]=0xb3;
			pString2[j*2+1]=0xc4;
			pString2[j*2+1+1]=0xc5;
		}
		pString[31]=0x20;
		pString[32]=0xb3;
		pString2[31]=0xc4;
		pString2[32]=0xb4;
		m_ClientDC.DrawString(x,y+16+(i*2)*16,pString,33,0,1);
		if(i!=15)	
			m_ClientDC.DrawString(x,y+32+(i*2)*16,pString2,33,0,1);
		if(i==8)
		{
			pString[0]=0xc4;
			m_ClientDC.SetTextColor(WISP_RGB(0xff,0,0));
			for(j=0;j<16;j++)
			{
				m_ClientDC.DrawString(x+12+j*24,y+(i*2)*16,pString,1,0,1);
			}
			m_ClientDC.SetTextColor(WISP_RGB(0,0,0xff));
		}
	}
	
	pString[0]=0xc0;
	for(i=0;i<16;i++)
	{
		pString[i*2+1]=0xc4;
		pString[i*2+2]=0xc1;
	}
	pString[32]=0xd9;
	m_ClientDC.DrawString(x,y+32+(15*2)*16,pString,33,0,1);
}
bool CIBMAsciiWnd::OnUpdateClient(IN WISP_MSG *pMsg)
{
	CWispForm::OnUpdateClient(pMsg);
	WCHAR pString[100];

	m_ClientDC.SetTextType(2);
	int x=28+60,y=24;
	DrawGrid(x,y,0,0);
	DrawIndex(x+12,y-16);

	memset(pString,0,sizeof(pString));
	int i,m,n;
	m_ClientDC.SetTextColor(ColorOption.clrText);
	m_ClientDC.SetTextColor(WISP_RGB(192,192,192));
	m_ClientDC.SetTextType(m_FontType);
	for(i = 1; i < 256; i++)
	{
		m=i/16;
		n=i%16;
		pString[0]=(WCHAR)i;
		m_ClientDC.DrawString(x+12+n*24,y+16+m*32,pString,1,0,1);
	}

	return false;
}

bool CIBMAsciiWnd::SetFont(int FontType)
{
	bool bOK=false;
	if(FontType>=2 && FontType<=4)
	{
		m_FontType=FontType;
		SetWindowText(m_gTitileName[FontType-2]);
		bOK=true;
	}	
	return bOK;
}
void CIBMAsciiWnd::Popup()
{
	if(IsWindow())
	{
		Show();
	}
	else
	{
		CreateForm(NULL);
	}
}

WCHAR* CIBMAsciiWnd::m_gTitileName[3]=
{
	WSTR("IBM ASCII"),	
	WSTR("EBCDIC"),
	WSTR("ANSI ASCII"),
};
WISP_FORM_RES_ITEM CIBMAsciiWnd::m_FormRes[]=
{	
	{
		WISP_CTRL_FORM,
		{0,0,500,600},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR(""),
		"\\SyserIcon\\Syser.ico",
	},
	{WISP_CTRL_NULL}
};