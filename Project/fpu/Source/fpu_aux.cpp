/*---------------------------------------------------------------------------+
 |  fpu_aux.c                                                                |
 |  $Id: fpu_aux.c,v 1.2 2001/10/06 03:53:46 bdenney Exp $
 |                                                                           |
 | Code to implement some of the FPU auxiliary instructions.                 |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997                                         |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@suburbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/
#include "fpu_i387.h"
#include "fpu_system.h"
#include "exception.h"
#include "fpu_emu.h"
#include "status_w.h"
#include "control_w.h"


static void fnop(current_i387_definefunyuan_void)
{
}

void fclex(current_i387_definefunyuan_void)
{
  partial_status &= ~(SW_Backward|SW_Summary|SW_Stack_Fault|SW_Precision|
		   SW_Underflow|SW_Overflow|SW_Zero_Div|SW_Denorm_Op|
		   SW_Invalid);
  no_ip_update = 1;
}

/* Needs to be externally visible */
void finit(current_i387_definefunyuan_void   )
{
  control_word = 0x037f;
  partial_status = 0;
  top = 0;            /* We don't keep top in the status word internally. */
  fpu_tag_word = 0xffff;
  /* The behaviour is different from that detailed in
     Section 15.1.6 of the Intel manual */
  operand_address.offset = 0;
  operand_address.selector = 0;
  instruction_address.offset = 0;
  instruction_address.selector = 0;
  instruction_address.opcode = 0;
  no_ip_update = 1;
}

/*
 * These are nops on the i387..
 */
#define feni fnop
#define fdisi fnop
#define fsetpm fnop

static FUNC const finit_table[] = {
  feni, fdisi, fclex, finit,
  fsetpm, FPU_illegal, FPU_illegal, FPU_illegal
};

void finit_(current_i387_definefunyuan_void   )
{
  (finit_table[FPU_rm])(current_i387_yuan_void);
}


static void fstsw_ax(current_i387_definefunyuan_void   )
{
  SET_AX(status_word()); // KPL
  no_ip_update = 1;
}

static FUNC const fstsw_table[] = {
  fstsw_ax,    FPU_illegal, FPU_illegal, FPU_illegal,
  FPU_illegal, FPU_illegal, FPU_illegal, FPU_illegal
};

void fstsw_(current_i387_definefunyuan_void   )
{
  (fstsw_table[FPU_rm])(current_i387_yuan_void);
}


static FUNC const fp_nop_table[] = {
  fnop, FPU_illegal, FPU_illegal, FPU_illegal,
  FPU_illegal, FPU_illegal, FPU_illegal, FPU_illegal
};

void fp_nop(current_i387_definefunyuan_void   )
{
  (fp_nop_table[FPU_rm])(current_i387_yuan_void);
}


void fld_i_(current_i387_definefunyuan_void   )
{
  FPU_REG *st_new_ptr;
  int i;
  u_char tag;

  if ( STACK_OVERFLOW )
    { FPU_stack_overflow(current_i387_yuan_clono  ); return; }

  /* fld st(i) */
  i = FPU_rm;
  if ( NOT_EMPTY(i) )
    {
      reg_copy(&st(i), st_new_ptr);
      tag = FPU_gettagi(current_i387_yuan_   i);
      push();
      FPU_settag0(current_i387_yuan_   tag);
    }
  else
    {
      if ( control_word & CW_Invalid )
	{
	  /* The masked response */
	  FPU_stack_underflow(current_i387_yuan_clono  );
	}
      else
	EXCEPTION(EX_StackUnder);
    }

}


void fxch_i(current_i387_definefunyuan_void   )
{
  /* fxch st(i) */
  FPU_REG t;
  int i = FPU_rm;
  FPU_REG *st0_ptr = &st(0), *sti_ptr = &st(i);
  s32 tag_word = fpu_tag_word;
  int regnr = top & 7, regnri = ((regnr + i) & 7);
  u_char st0_tag = (tag_word >> (regnr*2)) & 3;
  u_char sti_tag = (tag_word >> (regnri*2)) & 3;

  if ( st0_tag == TAG_Empty )
    {
      if ( sti_tag == TAG_Empty )
	{
	  FPU_stack_underflow(current_i387_yuan_clono  );
	  FPU_stack_underflow_i(current_i387_yuan_   i);
	  return;
	}
      if ( control_word & CW_Invalid )
	{
	  /* Masked response */
	  FPU_copy_to_reg0(current_i387_yuan_   sti_ptr, sti_tag);
	}
      FPU_stack_underflow_i(current_i387_yuan_   i);
      return;
    }
  if ( sti_tag == TAG_Empty )
    {
      if ( control_word & CW_Invalid )
	{
	  /* Masked response */
	  FPU_copy_to_regi(current_i387_yuan_   st0_ptr, st0_tag, i);
	}
      FPU_stack_underflow(current_i387_yuan_clono  );
      return;
    }
  clear_C1();

  reg_copy(st0_ptr, &t);
  reg_copy(sti_ptr, st0_ptr);
  reg_copy(&t, sti_ptr);

  tag_word &= ~(3 << (regnr*2)) & ~(3 << (regnri*2));
  tag_word |= (sti_tag << (regnr*2)) | (st0_tag << (regnri*2));
  fpu_tag_word = tag_word;
}


void ffree_(current_i387_definefunyuan_void   )
{
  /* ffree st(i) */
  FPU_settagi(current_i387_yuan_   FPU_rm, TAG_Empty);
}


void ffreep(current_i387_definefunyuan_void   )
{
  /* ffree st(i) + pop - unofficial code */
  FPU_settagi(current_i387_yuan_   FPU_rm, TAG_Empty);
  FPU_pop(current_i387_yuan_clono  );
}


void fst_i_(current_i387_definefunyuan_void   )
{
  /* fst st(i) */
  FPU_copy_to_regi(current_i387_yuan_   &st(0), FPU_gettag0(current_i387_yuan_doc  ), FPU_rm);
}


void fstp_i(current_i387_definefunyuan_void   )
{
  /* fstp st(i) */
  FPU_copy_to_regi(current_i387_yuan_   &st(0), FPU_gettag0(current_i387_yuan_doc  ), FPU_rm);
  FPU_pop(current_i387_yuan_clono  );
}

