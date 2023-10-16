#ifndef _SYSER_APP_CMD_H_
#define _SYSER_APP_CMD_H_


struct SYSER_APP_CMD_ENTRY
{
	WCHAR*	CmdStr;
	WCHAR*	CmdCmt;
	void*	CmdProc;
};

extern SYSER_APP_CMD_ENTRY	SyserAppCmdTable[];
class CSyserApp;

DECLARE_SYSER_APP_CMD(run_command);
DECLARE_SYSER_APP_CMD(start_command);
DECLARE_SYSER_APP_CMD(stop_command);
DECLARE_SYSER_APP_CMD(reloadconfig_command);
DECLARE_SYSER_APP_CMD(fio_command);
DECLARE_SYSER_APP_CMD(loadsds_command);
DECLARE_SYSER_APP_CMD(unloadsds_command);
DECLARE_SYSER_APP_CMD(tsf_command);
DECLARE_SYSER_APP_CMD(load_command);
DECLARE_SYSER_APP_CMD(install_command);
DECLARE_SYSER_APP_CMD(uninstall_command);
DECLARE_SYSER_APP_CMD(scrshot_command);
DECLARE_SYSER_APP_CMD(rmsptd_command);

class CConsoleWnd : public CWispConsoleWnd
{
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
};

#endif
