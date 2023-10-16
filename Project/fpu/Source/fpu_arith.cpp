/*---------------------------------------------------------------------------+
 |  fpu_arith.c                                                              |
 |  $Id: fpu_arith.c,v 1.3 2001/10/06 03:53:46 bdenney Exp $
 |                                                                           |
 | Code to implement the FPU register/register arithmetic instructions       |
 |                                                                           |
 | Copyright (C) 1992,1993,1997                                              |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@suburbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/
#include "fpu_i387.h"
#include "fpu_system.h"
#include "fpu_emu.h"
#include "control_w.h"
#include "status_w.h"

void fadd__(current_i387_definefunyuan_void   )
{
  /* fadd st,st(i) */
  int i = FPU_rm;
  clear_C1();
  FPU_add(current_i387_yuan_   &st(i), FPU_gettagi(current_i387_yuan_   i), 0, control_word);
}


void fmul__(current_i387_definefunyuan_void   )
{
  /* fmul st,st(i) */
  int i = FPU_rm;
  clear_C1();
  FPU_mul(current_i387_yuan_   &st(i), FPU_gettagi(current_i387_yuan_   i), 0, control_word);
}



void fsub__(current_i387_definefunyuan_void   )
{
  /* fsub st,st(i) */
  clear_C1();
  FPU_sub(current_i387_yuan_   0, REGNO2PTR(FPU_rm), control_word);
}


void fsubr_(current_i387_definefunyuan_void   )
{
  /* fsubr st,st(i) */
  clear_C1();
  FPU_sub(current_i387_yuan_   REV, REGNO2PTR(FPU_rm), control_word);
}


void fdiv__(current_i387_definefunyuan_void   )
{
  /* fdiv st,st(i) */
  clear_C1();
  FPU_div(current_i387_yuan_   0, REGNO2PTR(FPU_rm), control_word);
}


void fdivr_(current_i387_definefunyuan_void   )
{
  /* fdivr st,st(i) */
  clear_C1();
  FPU_div(current_i387_yuan_   REV, REGNO2PTR(FPU_rm), control_word);
}



void fadd_i(current_i387_definefunyuan_void   )
{
  /* fadd st(i),st */
  int i = FPU_rm;
  clear_C1();
  FPU_add(current_i387_yuan_   &st(i), FPU_gettagi(current_i387_yuan_   i), i, control_word);
}


void fmul_i(current_i387_definefunyuan_void   )
{
  /* fmul st(i),st */
  clear_C1();
  FPU_mul(current_i387_yuan_   &st(0), FPU_gettag0(current_i387_yuan_doc  ), FPU_rm, control_word);
}


void fsubri(current_i387_definefunyuan_void   )
{
  /* fsubr st(i),st */
  clear_C1();
  FPU_sub(current_i387_yuan_   DEST_RM, REGNO2PTR(FPU_rm), control_word);
}


void fsub_i(current_i387_definefunyuan_void   )
{
  /* fsub st(i),st */
  clear_C1();
  FPU_sub(current_i387_yuan_   REV|DEST_RM, REGNO2PTR(FPU_rm), control_word);
}


void fdivri(current_i387_definefunyuan_void   )
{
  /* fdivr st(i),st */
  clear_C1();
  FPU_div(current_i387_yuan_   DEST_RM, REGNO2PTR(FPU_rm), control_word);
}


void fdiv_i(current_i387_definefunyuan_void   )
{
  /* fdiv st(i),st */
  clear_C1();
  FPU_div(current_i387_yuan_   REV|DEST_RM, REGNO2PTR(FPU_rm), control_word);
}



void faddp_(current_i387_definefunyuan_void   )
{
  /* faddp st(i),st */
  int i = FPU_rm;
  clear_C1();
  if ( FPU_add(current_i387_yuan_   &st(i), FPU_gettagi(current_i387_yuan_   i), i, control_word) >= 0 )
    FPU_pop(current_i387_yuan_clono  );
}


void fmulp_(current_i387_definefunyuan_void   )
{
  /* fmulp st(i),st */
  clear_C1();
  if ( FPU_mul(current_i387_yuan_   &st(0), FPU_gettag0(current_i387_yuan_doc  ), FPU_rm, control_word) >= 0 )
    FPU_pop(current_i387_yuan_clono  );
}



void fsubrp(current_i387_definefunyuan_void   )
{
  /* fsubrp st(i),st */
  clear_C1();
  if ( FPU_sub(current_i387_yuan_   DEST_RM, REGNO2PTR(FPU_rm), control_word) >= 0 )
    FPU_pop(current_i387_yuan_clono  );
}


void fsubp_(current_i387_definefunyuan_void   )
{
  /* fsubp st(i),st */
  clear_C1();
  if ( FPU_sub(current_i387_yuan_   REV|DEST_RM, REGNO2PTR(FPU_rm), control_word) >= 0 )
    FPU_pop(current_i387_yuan_clono  );
}


void fdivrp(current_i387_definefunyuan_void   )
{
  /* fdivrp st(i),st */
  clear_C1();
  if ( FPU_div(current_i387_yuan_   DEST_RM, REGNO2PTR(FPU_rm), control_word) >= 0 )
    FPU_pop(current_i387_yuan_clono  );
}


void fdivp_(current_i387_definefunyuan_void   )
{
  /* fdivp st(i),st */
  clear_C1();
  if ( FPU_div(current_i387_yuan_   REV|DEST_RM, REGNO2PTR(FPU_rm), control_word) >= 0 )
    FPU_pop(current_i387_yuan_clono  );
}
