#include "StdAfx.h"
#include "BootOptionForm.h"
#include "SyserOptionApp.h"

enum CBootOptionForm::WISP_FORM_ID
{
	CMD_ID_BOOT_SYSTEM = WISP_ID_USER_START,
	CMD_ID_BOOT_AUTOMATIC,
	CMD_ID_BOOT_MANUAL
};

WISP_FORM_RES_ITEM CBootOptionForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,200,300},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Boot Mode")
	},
	{
		WISP_CTRL_STATIC_DIB,
		{70,30,32,32},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\Syser.ico:2"
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,180,280},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
	},
	{
		WISP_CTRL_RADIO_BOX,
		{70,110,100,20},
		CMD_ID_BOOT_SYSTEM,
		WISP_CBS_NORMAL,
		WSTR("System"),
		NULL,
	},
	{
		WISP_CTRL_RADIO_BOX,
		{70,160,100,20},
		CMD_ID_BOOT_AUTOMATIC,
		WISP_CBS_NORMAL,
		WSTR("Automatic"),
		NULL,
	},
	{
		WISP_CTRL_RADIO_BOX,
		{70,210,100,20},
		CMD_ID_BOOT_MANUAL,
		WISP_CBS_NORMAL,
		WSTR("Manual"),
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{70,250,60,18},
		WISP_ID_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CBootOptionForm)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CBootOptionForm)
	WISP_MSG_CMD_MAP(WISP_ID_OK,OnOK)
WISP_MSG_CMD_MAP_END


bool CBootOptionForm::OnFormCreate(IN WISP_MSG*pMsg)
{
	m_pSystemBT = (CWispRadioBox*)GetFormItem(CMD_ID_BOOT_SYSTEM);
	m_pAutoBT = (CWispRadioBox*)GetFormItem(CMD_ID_BOOT_AUTOMATIC);
	m_pManualBT = (CWispRadioBox*)GetFormItem(CMD_ID_BOOT_MANUAL);
	m_BootType = -1;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//读取驱动启动类型
	GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\Start",&m_BootType,sizeof(int));
	if(m_BootType<=0 || m_BootType>3)
	{
		m_BootType = 3;
		SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\Start",&m_BootType,REG_DWORD);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	switch(m_BootType)
	{
	case 1:
		m_pSystemBT->Check();
		break;
	case 2:
		m_pAutoBT->Check();
		break;
	case 3:
		m_pManualBT->Check();
		break;
	}
	m_OldBootType = m_BootType;
	return true;
}

bool CBootOptionForm::OnOK(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg != WISP_CMD_BT_UP)
		return true;
	if(m_pSystemBT->m_Style&WISP_WS_MARKED)
		m_BootType = 1;
	else if(m_pAutoBT->m_Style&WISP_WS_MARKED)
		m_BootType = 2;
	else if(m_pManualBT->m_Style&WISP_WS_MARKED)
		m_BootType = 3;
	else
		m_BootType = -1;
	if(m_OldBootType != m_BootType && m_BootType!=-1)
	{
		if(theApp.m_VersionInfo.dwMajorVersion>=6 && m_BootType<3)
		{
			::MessageBox(theApp.m_hLocalWnd,"If you choose this boot type , you must close Vista Aero effect!","Warning",MB_OK);
		}
		if(m_BootType < 3 && SyserOption.iVideoDetectMode==SYSER_VDM_USER)
		{
			::MessageBox(theApp.m_hLocalWnd,"Change Video Detect Mode to \"Auto\" to support this boot type","Warning",MB_OK);
			SyserOption.iVideoDetectMode = SYSER_VDM_AUTO;
			if(SaveSyserOption(theApp.m_szSyserCfgFN,&SyserOption,sizeof(SyserOption))==false)
				::MessageBox(theApp.m_hLocalWnd,"Fail to save Syser.cfg !","Error",MB_OK);
		}
		SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\Start",&m_BootType,REG_DWORD);
	}
	return true;
}
