#ifndef _SHARECMD_H_
#define _SHARECMD_H_
extern SYSER_CMD_ENTRY	ShareCmdTable[];
DECLARE_SYSER_CMD(wmsg_command);
DECLARE_SYSER_CMD(zap_command);
DECLARE_SYSER_CMD(errorcode_command);
DECLARE_SYSER_CMD(ntstatus_command);
DECLARE_SYSER_CMD(ioctl_command);
DECLARE_SYSER_CMD(lines_command);
DECLARE_SYSER_CMD(width_command);
DECLARE_SYSER_CMD(window_resize_command);
DECLARE_SYSER_CMD(bugcheckcode_command);
DECLARE_SYSER_CMD(file_command);
DECLARE_SYSER_CMD(watch_source_command);
DECLARE_SYSER_CMD(table_source_command);
DECLARE_SYSER_CMD(crc_command);

#endif //_SHARECMD_H_