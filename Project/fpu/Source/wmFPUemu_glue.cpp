//  Copyright (C) 2001  MandrakeSoft S.A.
//
//    MandrakeSoft S.A.
//    43, rue d'Aboukir
//    75002 Paris - France
//    http://www.linux-mandrake.com/
//    http://www.mandrakesoft.com/
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA


//
// This is the glue logic needed to connect the wm-FPU-emu
// FPU emulator written by Bill Metzenthen to bochs.
//

#include "../../IntelCPU/Source/x86cpu.h"
#include "fpu_i387.h"

//#include <math.h>

#if !BX_WITH_MACOS
extern "C++" {
#endif
#include "fpu_emu.h"
#include "linux/signal.h"

#if !BX_WITH_MACOS
}
#endif

#undef LOG_THIS
#define LOG_THIS genlog->
#if BX_USE_CPU_SMF
//#define this (BX_CPU(0))
#define this BX_CPU_THIS
#endif

// Use this to hold a pointer to the instruction since
// we can't pass this to the FPU emulation routines, which
// will ultimately call routines here.


//static bxInstruction_c *bx_fcpu_i387->fpu_iptr_ = NULL;
//static BX_CPU_C *bx_fcpu_i387->fpu_cpu_ptr_ = NULL;
//static i387_t *bx_fcpu_i387->current_i387_;


//static BX_FCPU_I387 *bx_fcpu_i387;
//bx_fcpu_i387->current_i387_
//bx_fcpu_i387->fpu_cpu_ptr_
//bx_fcpu_i387->fpu_iptr_

 void
math_emulate2(current_i387_definefunyuan_   fpu_addr_modes addr_modes,
              u_char  FPU_modrm,
              u_char byte1,
              void *data_address,
              struct address data_sel_off,
              struct address entry_sel_off);

 void 
printfp(char *s, FPU_REG *r);

#if BX_SUPPORT_FPU==1
  // This is called by bochs upon reset
  void
BX_CPU_C::fpu_init(void)
{
  BX_FCPU_I387 bx_fcpu_i387_s,*bx_fcpu_i387;
  bx_fcpu_i387 = &bx_fcpu_i387_s;

  bx_fcpu_i387->current_i387_ = &(BX_CPU_THIS_PTR the_i387);
  finit(current_i387_yuan_clono  );
}

#endif

  void
BX_CPU_C::fpu_execute(bxInstruction_c *i)
{

  fpu_addr_modes addr_modes;
  void *data_address;
  struct address data_sel_off;
  struct address entry_sel_off;
  bx_bool is_32;

  BX_FCPU_I387 bx_fcpu_i387_s,*bx_fcpu_i387;
  bx_fcpu_i387 = &bx_fcpu_i387_s;

  bx_fcpu_i387->fpu_iptr_ = i;
  bx_fcpu_i387->fpu_cpu_ptr_ = this;
  bx_fcpu_i387->current_i387_ = &(BX_CPU_THIS_PTR the_i387);

  BX_CPU_C *icpu = this;


#if 0
  addr_modes.default_mode = VM86;
  addr_modes.default_mode = 0; // FPU_CS == __USER_CS && FPU_DS == __USER_DS
  addr_modes.default_mode = SEG32;
  addr_modes.default_mode = PM16;
#endif
  if (protected_mode()) {
    addr_modes.default_mode = SEG32;
    }
  else if (v8086_mode()) {
    addr_modes.default_mode = VM86;
    }
  else {
    // real mode, use vm86 for now
    addr_modes.default_mode = VM86;
    }


  // Mark if instruction used opsize or addrsize prefixes
  // Actually, addr_modes.override.address_size is not used,
  // could delete that code.
  is_32 = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.d_b;
  if (i->as32B() == is_32)
    addr_modes.override.address_size = 0;
  else
    addr_modes.override.address_size = ADDR_SIZE_PREFIX;
  if (i->os32B() == is_32)
    addr_modes.override.operand_size = 0;
  else
    addr_modes.override.operand_size = OP_SIZE_PREFIX;

  // For now set access_limit to max.  It seems to be
  // a number from 0..255 denoting how many bytes the
  // current instruction can access according to its
  // memory operand.  255 means >= 255.
access_limit = 0xff;

  // fill in orig eip here in offset
  // fill in CS in selector
  entry_sel_off.offset = BX_CPU_THIS_PTR prev_eip;
  entry_sel_off.selector = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value;

// should set these fields to 0 if mem operand not used
  data_address = (void *) RMAddr(i);
  data_sel_off.offset = RMAddr(i);
  data_sel_off.selector = BX_CPU_THIS_PTR program_visible_sregs[i->seg()].selector.value;


  math_emulate2(current_i387_yuan_   addr_modes, i->modrm(), i->b1(), data_address,
                data_sel_off, entry_sel_off);

}


static double sigh_scale_factor = 4.6566128730773926e-010;
static double sigl_scale_factor = 1.0842021724855044e-019;

//static double sigh_scale_factor = pow(2.0, -31.0);
//static double sigl_scale_factor = pow(2.0, -63.0);

//vc7 pow_p4 RavDos下有问题
/*
void
BX_CPU_C::fpu_print_regs()
{
  Bit32u reg;

  BX_FCPU_I387 bx_fcpu_i387_s,*bx_fcpu_i387;
  bx_fcpu_i387 = &bx_fcpu_i387_s;

  reg = i387.soft.cwd;
  fprintf(stderr, "cwd            0x%-8x\t%d\n", (unsigned) reg, (int) reg);
  reg = i387.soft.swd;
  fprintf(stderr, "swd            0x%-8x\t%d\n", (unsigned) reg, (int) reg);
  reg = i387.soft.twd;
  fprintf(stderr, "twd            0x%-8x\t%d\n", (unsigned) reg, (int) reg);
  reg = i387.soft.fip;
  fprintf(stderr, "fip            0x%-8x\t%d\n", (unsigned) reg, (int) reg);
  reg = i387.soft.fcs;
  fprintf(stderr, "fcs            0x%-8x\t%d\n", (unsigned) reg, (int) reg);
  reg = i387.soft.foo;
  fprintf(stderr, "foo            0x%-8x\t%d\n", (unsigned) reg, (int) reg);
  reg = i387.soft.fos;
  fprintf(stderr, "fos            0x%-8x\t%d\n", (unsigned) reg, (int) reg);
  // print stack too
  for (int i=0; i<8; i++) {
    FPU_REG *fpr = &st(i);
    double f1 = 0;//pow(2.0, ((0x7fff&fpr->exp) - EXTENDED_Ebias));
    if (fpr->exp & SIGN_Negative) f1 = -f1;
    double f2 = ((double)fpr->sigh * sigh_scale_factor);
    double f3 = ((double)fpr->sigl * sigl_scale_factor);
    double f = f1*(f2+f3);
    fprintf(stderr, "st%d            %.10f (raw 0x%04x%08x%08x)\n", i, f, 0xffff&fpr->exp, fpr->sigh, fpr->sigl);
  }
}
*/
  unsigned
fpu_get_ds(current_i387_definefunyuan_void)
{
  return(bx_fcpu_i387->fpu_cpu_ptr_->program_visible_sregs[BX_SEG_REG_DS].selector.value);
}

  void
fpu_set_ax(current_i387_definefunyuan_   unsigned short val16)
{
// define to set AX in the current CPU -- not ideal.
#undef AX
#define AX (bx_fcpu_i387->fpu_cpu_ptr_->program_visible_gen_reg[0].word.rx)
  AX = val16;
#undef AX
//BX_DEBUG(( "fpu_set_ax(0x%04x)", (unsigned) val16));
}

  void
fpu_verify_area(current_i387_definefunyuan_   unsigned what, void *ptr, unsigned n)
{
  bx_segment_reg_t *seg;

  seg = &bx_fcpu_i387->fpu_cpu_ptr_->program_visible_sregs[bx_fcpu_i387->fpu_iptr_->seg()];

  if (what == VERIFY_READ) {
    bx_fcpu_i387->fpu_cpu_ptr_->read_virtual_checks(seg, PTR2INT(ptr), n);
    }
  else {  // VERIFY_WRITE
    bx_fcpu_i387->fpu_cpu_ptr_->write_virtual_checks(seg, PTR2INT(ptr), n);
    }
//BX_DEBUG(( "verify_area: 0x%x", PTR2INT(ptr)));
}


  void
FPU_printall(current_i387_definefunyuan_void)
{
  BX_PANIC(("FPU_printall"));
}


  unsigned
fpu_get_user(current_i387_definefunyuan_   void *ptr, unsigned len)
{
  Bit32u val32;
  Bit16u val16;
  Bit8u  val8;

  switch (len) {
    case 1:
      bx_fcpu_i387->fpu_cpu_ptr_->read_virtual_byte(bx_fcpu_i387->fpu_iptr_->seg(), PTR2INT(ptr), &val8);
      val32 = val8;
      break;
    case 2:
      bx_fcpu_i387->fpu_cpu_ptr_->read_virtual_word(bx_fcpu_i387->fpu_iptr_->seg(), PTR2INT(ptr), &val16);
      val32 = val16;
      break;
    case 4:
      bx_fcpu_i387->fpu_cpu_ptr_->read_virtual_dword(bx_fcpu_i387->fpu_iptr_->seg(), PTR2INT(ptr), &val32);
      break;
    default:
      BX_PANIC(("fpu_get_user: len=%u", len));
    }
  return(val32);
}

  void
fpu_put_user(current_i387_definefunyuan_   unsigned val, void *ptr, unsigned len)
{
  Bit32u val32;
  Bit16u val16;
  Bit8u  val8;

  switch (len) {
    case 1:
      val8 = val;
      bx_fcpu_i387->fpu_cpu_ptr_->write_virtual_byte(bx_fcpu_i387->fpu_iptr_->seg(), PTR2INT(ptr), &val8);
      break;
    case 2:
      val16 = val;
      bx_fcpu_i387->fpu_cpu_ptr_->write_virtual_word(bx_fcpu_i387->fpu_iptr_->seg(), PTR2INT(ptr), &val16);
      break;
    case 4:
      val32 = val;
      bx_fcpu_i387->fpu_cpu_ptr_->write_virtual_dword(bx_fcpu_i387->fpu_iptr_->seg(), PTR2INT(ptr), &val32);
      break;
    default:
      BX_PANIC(("fpu_put_user: len=%u", len));
    }
}

  void
math_abort(current_i387_definefunyuan_   struct info *info, unsigned int signal)
{
  UNUSED(info); // info is always passed NULL
#if BX_CPU_LEVEL >= 4

// values of signal:
//   SIGILL  : opcodes which are illegal
//   SIGFPE  : unmasked FP exception before WAIT or non-control instruction
//   SIGSEGV : access data beyond segment violation
  switch (signal) {
    case SIGFPE:
      if (bx_fcpu_i387->fpu_cpu_ptr_->cr0.ne == 0) {
        // MSDOS compatibility external interrupt (IRQ13)
        BX_PANIC (("math_abort: MSDOS compatibility not supported yet"));
        }
      bx_fcpu_i387->fpu_cpu_ptr_->exception(BX_MF_EXCEPTION, 0, 0);
      // execution does not reach here

    case SIGILL:
      BX_PANIC (("math_abort: SIGILL not implemented yet."));
      break;
    case SIGSEGV:
      BX_PANIC (("math_abort: SIGSEGV not implemented yet."));
      break;
    }

#else
  UNUSED(signal);
  BX_INFO(("math_abort: CPU<4 not supported yet"));
#endif
}

  int
fpu_printk(const char * fmt, ...)
{
  BX_INFO(("fpu_printk not complete: %s", fmt));
  return(0); // for now
}
