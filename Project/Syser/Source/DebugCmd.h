#ifndef _DEBUG_CMD_H_
#define _DEBUG_CMD_H_

DECLARE_SYSER_CMD(exit_system_command);
DECLARE_SYSER_CMD(go_command);
DECLARE_SYSER_CMD(trace_command);
DECLARE_SYSER_CMD(source_trace_command);
DECLARE_SYSER_CMD(trace_branch_command);
DECLARE_SYSER_CMD(bc_command);
DECLARE_SYSER_CMD(bl_command);
DECLARE_SYSER_CMD(bd_command);
DECLARE_SYSER_CMD(be_command);
DECLARE_SYSER_CMD(bpx_command);
DECLARE_SYSER_CMD(bpload_command);
DECLARE_SYSER_CMD(bpm_command);
DECLARE_SYSER_CMD(bpio_command);
DECLARE_SYSER_CMD(p_command);
DECLARE_SYSER_CMD(source_proceed_command);
DECLARE_SYSER_CMD(skip_command);
DECLARE_SYSER_CMD(u_command);
DECLARE_SYSER_CMD(cpu_command);
DECLARE_SYSER_CMD(r_command);
DECLARE_SYSER_CMD(s_command);
DECLARE_SYSER_CMD(c_command);
DECLARE_SYSER_CMD(a_command);
DECLARE_SYSER_CMD(e_command);
DECLARE_SYSER_CMD(m_command);
DECLARE_SYSER_CMD(f_command);
DECLARE_SYSER_CMD(seg_command);
DECLARE_SYSER_CMD(cmt_command);
DECLARE_SYSER_CMD(stack_command);
DECLARE_SYSER_CMD(src_command);
DECLARE_SYSER_CMD(bpmsg_command);
DECLARE_SYSER_CMD(sym_command);
DECLARE_SYSER_CMD(symmod_command);
DECLARE_SYSER_CMD(sdsmod_command);
DECLARE_SYSER_CMD(mod_command);
DECLARE_SYSER_CMD(test_command11);

#ifdef CODE_OS_WIN
DECLARE_SYSER_CMD(open_command);
DECLARE_SYSER_CMD(close_command);
DECLARE_SYSER_CMD(reset_command);
#endif

extern SYSER_CMD_ENTRY DebugCmdTable[];

#endif
