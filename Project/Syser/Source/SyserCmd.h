#ifndef _SYSER_CMD_
#define _SYSER_CMD_

#include "DbgProcess.h"
#include "USBCmd.h"

extern SYSER_CMD_ENTRY	SysCmdTable[];

DECLARE_SYSER_CMD(f_command);
DECLARE_SYSER_CMD(objtab_command);
DECLARE_SYSER_CMD(bpt_command);
DECLARE_SYSER_CMD(bpp_command);
//DECLARE_SYSER_CMD(bpr_command);

DECLARE_SYSER_CMD(m_command);
DECLARE_SYSER_CMD(ioapic_command);
DECLARE_SYSER_CMD(localapic_command);
DECLARE_SYSER_CMD(export_command);
DECLARE_SYSER_CMD(test_command);
DECLARE_SYSER_CMD(addr_command);
DECLARE_SYSER_CMD(proc_command);
DECLARE_SYSER_CMD(ver_command);
DECLARE_SYSER_CMD(data_command);
DECLARE_SYSER_CMD(code_command);

DECLARE_SYSER_CMD(cpuid_command);
DECLARE_SYSER_CMD(set_softice_baseaddress_command);
DECLARE_SYSER_CMD(d_softice_command);
DECLARE_SYSER_CMD(u_softice_command);
DECLARE_SYSER_CMD(ib_command);
DECLARE_SYSER_CMD(ob_command);

DECLARE_SYSER_CMD(setkeyboardLED_command);
DECLARE_SYSER_CMD(DebugRegisterMonitor_command);
DECLARE_SYSER_CMD(r_command);
DECLARE_SYSER_CMD(pci_command);
DECLARE_SYSER_CMD(skip_command);
DECLARE_SYSER_CMD(ignore_command);
DECLARE_SYSER_CMD(p_command);
DECLARE_SYSER_CMD(page_command);
DECLARE_SYSER_CMD(phys_command);
DECLARE_SYSER_CMD(idt_command);
DECLARE_SYSER_CMD(gdt_command);
DECLARE_SYSER_CMD(ldt_command);
DECLARE_SYSER_CMD(tss_command);
DECLARE_SYSER_CMD(irq_command);
DECLARE_SYSER_CMD(msr_command);
DECLARE_SYSER_CMD(peekb_command);
DECLARE_SYSER_CMD(peekw_command);
DECLARE_SYSER_CMD(peekd_command);
DECLARE_SYSER_CMD(pokeb_command);
DECLARE_SYSER_CMD(pokew_command);
DECLARE_SYSER_CMD(poked_command);
DECLARE_SYSER_CMD(bpint_command);
DECLARE_SYSER_CMD(ntcall_command);
DECLARE_SYSER_CMD(ntcall2_command);
DECLARE_SYSER_CMD(objdir_command);
DECLARE_SYSER_CMD(device_command);
DECLARE_SYSER_CMD(driver_command);
DECLARE_SYSER_CMD(kmutex_command);
DECLARE_SYSER_CMD(kevent_command);
DECLARE_SYSER_CMD(ksem_command);
DECLARE_SYSER_CMD(peek_command);
DECLARE_SYSER_CMD(poke_command);
DECLARE_SYSER_CMD(msr_command);
DECLARE_SYSER_CMD(pagein_command);
DECLARE_SYSER_CMD(i3here_command);
DECLARE_SYSER_CMD(i1here_command);
DECLARE_SYSER_CMD(genint_command);
DECLARE_SYSER_CMD(exp_command);
DECLARE_SYSER_CMD(hboot_command);
DECLARE_SYSER_CMD(wf1_command);
DECLARE_SYSER_CMD(help_command);
DECLARE_SYSER_CMD(beep_command);
DECLARE_SYSER_CMD(syser_heap_information);
DECLARE_SYSER_CMD(vad_command);
DECLARE_SYSER_CMD(pte_command);
DECLARE_SYSER_CMD(set_softice_baseaddress_command);
DECLARE_SYSER_CMD(d_softice_command);
DECLARE_SYSER_CMD(u_softice_command);
DECLARE_SYSER_CMD(activesoftice_command);
DECLARE_SYSER_CMD(ikey_command);
DECLARE_SYSER_CMD(window_center_command);
DECLARE_SYSER_CMD(sysertest);
DECLARE_SYSER_CMD(dispinfo_command);
DECLARE_SYSER_CMD(sdsrv_command);
DECLARE_SYSER_CMD(plugin_command);
DECLARE_SYSER_CMD(syserheapinfo_command);
DECLARE_SYSER_CMD(acpi_shutdown_command);
DECLARE_SYSER_CMD(TerminateProcess_command);
DECLARE_SYSER_CMD(faults_command);
DECLARE_SYSER_CMD(handle_command);
DECLARE_SYSER_CMD(dt_command);
DECLARE_SYSER_CMD(lastbranch_command);
#endif /* _SYSER_CMD_ */

