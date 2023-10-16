#include "StdAfx.h"
#include "Syser.h"

WISP_MSG_MAP_BEGIN(CSSERegisterList)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_GET_FOCUS,OnGetFocus)
WISP_MSG_MAP_END(CWispList)

CSSERegisterList::CSSERegisterList(void)
{
	ZeroMemory(m_OldXMMRegister,sizeof(m_OldXMMRegister));
};

bool CSSERegisterList::OnGetFocus(IN WISP_MSG*pMsg)
{
	HANDLE hItem = GetNextItem(NULL);
	if(hItem)
		SelectItem(hItem);
	return true;
}

bool CSSERegisterList::OnCreate(IN WISP_MSG*pMsg)
{
	m_ChgColor = ColorOption.clrChgText;
	m_NormalColor = ColorOption.clrText;
	m_SelectBKColor = ColorOption.clrSelectedFrame;

	SetDefaultTextColor(m_NormalColor);
	SetBGColor(ColorOption.clrBackground);

	InsertColumn(WISP_STR("Register"),60);
	InsertColumn(WISP_STR("Value"),240,WISP_WLCS_EDITABLE);
	m_hSSE128RegItem[SSE_REG_0] = InsertItem(WISP_STR("XMM0"));
	m_hSSE128RegItem[SSE_REG_1] = InsertItem(WISP_STR("XMM1"));
	m_hSSE128RegItem[SSE_REG_2] = InsertItem(WISP_STR("XMM2"));
	m_hSSE128RegItem[SSE_REG_3] = InsertItem(WISP_STR("XMM3"));
	m_hSSE128RegItem[SSE_REG_4] = InsertItem(WISP_STR("XMM4"));
	m_hSSE128RegItem[SSE_REG_5] = InsertItem(WISP_STR("XMM5"));
	m_hSSE128RegItem[SSE_REG_6] = InsertItem(WISP_STR("XMM6"));
	m_hSSE128RegItem[SSE_REG_7] = InsertItem(WISP_STR("XMM7"));
	ResetContext();
	return true;
}

void CSSERegisterList::UpdateContext()
{
#ifdef CODE_OS_NT_DRV
	DWORD dwCR0,dwCR4,dwTmp;
	WISP_CHAR DisplayBuf[64];
	DWORD *pValue;
	int i,j;
	dwCR0 = GetCR0Register();
	dwCR4 = GetCR4Register();
	if(dwCR0 & 4)	
		return;
	if((gpCPUIDInfo[1].dwEDX & 0x2000000) == 0)
		return;
	if((dwCR4 & 0x200) == 0)
		return;
	if(SyserGetFpuErrorState())
		return ;	
	dwTmp = (DWORD)FxsaveBuffer;
	dwTmp &= 0xfffffff0;

	X86_FXSAVE((BYTE *)dwTmp);
	pValue = (DWORD *)(160+dwTmp);
	for(i = 0; i < 8; i++)
	{
		TSPrintf(DisplayBuf,WSTR("%08x %08x %08x %08x"),pValue[3],pValue[2],pValue[1],pValue[0]);
		SetItemText(m_hSSE128RegItem[i],1,DisplayBuf);
		for(j=0;j<4;j++)
		{
			if(pValue[j]!=m_OldXMMRegister[i][j])
			{
				m_OldXMMRegister[i][j] = pValue[j];
				SetItemTextColor(m_hSSE128RegItem[i],1,m_ChgColor);
				break;
			}
		}
		if(j==4)
			SetItemTextColor(m_hSSE128RegItem[i],1,m_NormalColor);
		pValue = pValue+4;
	}
#endif
}

void CSSERegisterList::ResetContext()
{
	SelectItem(m_hSSE128RegItem[SSE_REG_0]);
	SetItemText(m_hSSE128RegItem[SSE_REG_0],1,WSTR("????????"));
	SetItemText(m_hSSE128RegItem[SSE_REG_1],1,WSTR("????????"));
	SetItemText(m_hSSE128RegItem[SSE_REG_2],1,WSTR("????????"));
	SetItemText(m_hSSE128RegItem[SSE_REG_3],1,WSTR("????????"));
	SetItemText(m_hSSE128RegItem[SSE_REG_4],1,WSTR("????????"));
	SetItemText(m_hSSE128RegItem[SSE_REG_5],1,WSTR("????????"));
	SetItemText(m_hSSE128RegItem[SSE_REG_6],1,WSTR("????????"));
	SetItemText(m_hSSE128RegItem[SSE_REG_7],1,WSTR("????????"));
}

