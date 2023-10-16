#include "StdAfx.h"
#include "VideoModeForm.h"
#include "SyserOptionApp.h"

enum CVideoModeForm::WISP_FORM_ID
{
	CMD_ID_VDM_AUTO = WISP_ID_USER_START,
	CMD_ID_VDM_USER,
	CMD_ID_VDM_KERNEL
};

WISP_FORM_RES_ITEM CVideoModeForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,300,300},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Video Detect Mode")
	},
	{
		WISP_CTRL_STATIC_DIB,
		{123,30,32,32},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\Syser.ico:2"
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,280,280},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("You must restart syser to apply"),
	},
	{
		WISP_CTRL_RADIO_BOX,
		{60,110,260,20},
		CMD_ID_VDM_AUTO,
		WISP_CBS_NORMAL,
		WSTR("Auto (if you don't care)"),
		NULL,
	},
	{
		WISP_CTRL_RADIO_BOX,
		{60,160,260,20},
		CMD_ID_VDM_USER,
		WISP_CBS_NORMAL,
		WSTR("User Mode (High Compatibility)"),
		NULL,
	},
	{
		WISP_CTRL_RADIO_BOX,
		{60,210,260,20},
		CMD_ID_VDM_KERNEL,
		WISP_CBS_NORMAL,
		WSTR("Kernel Mode (Supports DirectX)"),
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{120,250,60,18},
		WISP_ID_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CVideoModeForm)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CVideoModeForm)
	WISP_MSG_CMD_MAP(WISP_ID_OK,OnOK)
WISP_MSG_CMD_MAP_END


bool CVideoModeForm::OnFormCreate(IN WISP_MSG*pMsg)
{
	m_pAutoBT = (CWispRadioBox*)GetFormItem(CMD_ID_VDM_AUTO);
	m_pUserBT = (CWispRadioBox*)GetFormItem(CMD_ID_VDM_USER);
	m_pKernelBT = (CWispRadioBox*)GetFormItem(CMD_ID_VDM_KERNEL);
	if(LoadSyserOption(theApp.m_szSyserCfgFN,&SyserOption,sizeof(SyserOption))==false)
	{
		SaveSyserOption(theApp.m_szSyserCfgFN,&OrgSyserOption,sizeof(OrgSyserOption));
		SyserOption = OrgSyserOption;
	}
	m_VideoModeType = SyserOption.iVideoDetectMode;
	switch(m_VideoModeType)
	{
	case SYSER_VDM_AUTO:
		m_pAutoBT->Check();
		break;
	case SYSER_VDM_USER:
		m_pUserBT->Check();
		break;
	case SYSER_VDM_KERNEL:
		m_pKernelBT->Check();
		break;
	}
	m_OldVideoModeType = m_VideoModeType;
	return true;
}

bool CVideoModeForm::OnOK(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg != WISP_CMD_BT_UP)
		return true;
	if(m_pAutoBT->m_Style&WISP_WS_MARKED)
		m_VideoModeType = SYSER_VDM_AUTO;
	else if(m_pUserBT->m_Style&WISP_WS_MARKED)
		m_VideoModeType = SYSER_VDM_USER;
	else if(m_pKernelBT->m_Style&WISP_WS_MARKED)
		m_VideoModeType = SYSER_VDM_KERNEL;
	else
		m_VideoModeType = -1;
	if(m_OldVideoModeType != m_VideoModeType && m_VideoModeType!=-1)
	{
		SyserOption.iVideoDetectMode = m_VideoModeType;
		SaveSyserOption(theApp.m_szSyserCfgFN,&SyserOption,sizeof(SyserOption));
	}
	return true;
}
