/*---------------------------------------------------------------------------+
 |  fpu_tags.c                                                               |
 |  $Id: fpu_tags.c,v 1.2 2001/10/06 03:53:46 bdenney Exp $
 |                                                                           |
 |  Set FPU register tags.                                                   |
 |                                                                           |
 | Copyright (C) 1997                                                        |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@jacobi.maths.monash.edu.au                |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/
#include "fpu_i387.h"
#include "fpu_emu.h"
#include "fpu_system.h"
#include "exception.h"


void FPU_pop(current_i387_definefunyuan_void)
{
  fpu_tag_word |= 3 << ((top & 7)*2);
  top++;
}


int FPU_gettag0(current_i387_definefunyuan_void)
{
  return (fpu_tag_word >> ((top & 7)*2)) & 3;
}


int FPU_gettagi(current_i387_definefunyuan_   int stnr)
{
  return (fpu_tag_word >> (((top+stnr) & 7)*2)) & 3;
}


int FPU_gettag(current_i387_definefunyuan_   int regnr)
{
  return (fpu_tag_word >> ((regnr & 7)*2)) & 3;
}


void FPU_settag0(current_i387_definefunyuan_   int tag)
{
  int regnr = top;
  regnr &= 7;
  fpu_tag_word &= ~(3 << (regnr*2));
  fpu_tag_word |= (tag & 3) << (regnr*2);
}


void FPU_settagi(current_i387_definefunyuan_   int stnr, int tag)
{
  int regnr = stnr+top;
  regnr &= 7;
  fpu_tag_word &= ~(3 << (regnr*2));
  fpu_tag_word |= (tag & 3) << (regnr*2);
}


void FPU_settag(current_i387_definefunyuan_   int regnr, int tag)
{
  regnr &= 7;
  fpu_tag_word &= ~(3 << (regnr*2));
  fpu_tag_word |= (tag & 3) << (regnr*2);
}


int FPU_Special(current_i387_definefunyuan_   FPU_REG const *ptr)
{
  int exp = exponent(ptr);

  if ( exp == EXP_BIAS+EXP_UNDER )
    return TW_Denormal;
  else if ( exp != EXP_BIAS+EXP_OVER )
    return TW_NaN;
  else if ( (ptr->sigh == 0x80000000) && (ptr->sigl == 0) )
    return TW_Infinity;
  return TW_NaN;
}


int isNaN(current_i387_definefunyuan_   FPU_REG const *ptr)
{
  return ( (exponent(ptr) == EXP_BIAS+EXP_OVER)
	   && !((ptr->sigh == 0x80000000) && (ptr->sigl == 0)) );
}


int FPU_empty_i(current_i387_definefunyuan_   int stnr)
{
  int regnr = (top+stnr) & 7;

  return ((fpu_tag_word >> (regnr*2)) & 3) == TAG_Empty;
}


int FPU_stackoverflow(current_i387_definefunyuan_   FPU_REG **st_new_ptr)
{
  *st_new_ptr = &st(-1);

  return ((fpu_tag_word >> (((top - 1) & 7)*2)) & 3) != TAG_Empty;
}


void FPU_copy_to_regi(current_i387_definefunyuan_   FPU_REG const *r, u_char tag, int stnr)
{
  reg_copy(r, &st(stnr));
  FPU_settagi(current_i387_yuan_   stnr, tag);
}

void FPU_copy_to_reg1(current_i387_definefunyuan_   FPU_REG const *r, u_char tag)
{
  reg_copy(r, &st(1));
  FPU_settagi(current_i387_yuan_   1, tag);
}

void FPU_copy_to_reg0(current_i387_definefunyuan_   FPU_REG const *r, u_char tag)
{
  int regnr = top;
  regnr &= 7;

  reg_copy(r, &st(0));

  fpu_tag_word &= ~(3 << (regnr*2));
  fpu_tag_word |= (tag & 3) << (regnr*2);
}
