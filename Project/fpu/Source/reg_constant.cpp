/*---------------------------------------------------------------------------+
 |  reg_constant.c                                                           |
 |  $Id: reg_constant.c,v 1.3 2001/10/06 03:53:46 bdenney Exp $
 |                                                                           |
 | All of the constant FPU_REGs                                              |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997                                         |
 |                     W. Metzenthen, 22 Parker St, Ormond, Vic 3163,        |
 |                     Australia.  E-mail   billm@suburbia.net               |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/
#include "fpu_i387.h"
#include "fpu_system.h"
#include "fpu_emu.h"
#include "status_w.h"
#include "reg_constant.h"
#include "control_w.h"



FPU_REG const CONST_1    = MAKE_REG(POS, 0, 0x00000000, 0x80000000);
FPU_REG const CONST_2    = MAKE_REG(POS, 1, 0x00000000, 0x80000000);
FPU_REG const CONST_HALF = MAKE_REG(POS, -1, 0x00000000, 0x80000000);
FPU_REG const CONST_L2T  = MAKE_REG(POS, 1, 0xcd1b8afe, 0xd49a784b);
FPU_REG const CONST_L2E  = MAKE_REG(POS, 0, 0x5c17f0bc, 0xb8aa3b29);
FPU_REG const CONST_PI   = MAKE_REG(POS, 1, 0x2168c235, 0xc90fdaa2);
// bbd: make CONST_PI2 non-const so that you can write "&CONST_PI2" when
// calling a function.  Otherwise you get const warnings.  Surely there's
// a better way.
FPU_REG CONST_PI2  = MAKE_REG(POS, 0, 0x2168c235, 0xc90fdaa2);
FPU_REG const CONST_PI4  = MAKE_REG(POS, -1, 0x2168c235, 0xc90fdaa2);
FPU_REG const CONST_LG2  = MAKE_REG(POS, -2, 0xfbcff799, 0x9a209a84);
FPU_REG const CONST_LN2  = MAKE_REG(POS, -1, 0xd1cf79ac, 0xb17217f7);

/* Extra bits to take pi/2 to more than 128 bits precision. */
FPU_REG const CONST_PI2extra = MAKE_REG(NEG,-66,0xfc8f8cbb,0xece675d1);

/* Only the sign (and tag) is used in internal zeroes */
FPU_REG const CONST_Z    = MAKE_REG(POS, EXP_UNDER, 0x0, 0x0);

/* Only the sign and significand (and tag) are used in internal NaNs */
/* The 80486 never generates one of these 
FPU_REG const CONST_SNAN = MAKE_REG(POS, EXP_OVER, 0x00000001, 0x80000000);
 */
/* This is the real indefinite QNaN */
FPU_REG const CONST_QNaN = MAKE_REG(NEG, EXP_OVER, 0x00000000, 0xC0000000);

/* Only the sign (and tag) is used in internal infinities */
FPU_REG const CONST_INF  = MAKE_REG(POS, EXP_OVER, 0x00000000, 0x80000000);

static void fld_const(current_i387_definefunyuan_   FPU_REG const *c, int adj, u_char tag)
{
  FPU_REG *st_new_ptr;

  if ( STACK_OVERFLOW )
    {
      FPU_stack_overflow(current_i387_yuan_clono  );
      return;
    }
  push();
  reg_copy(c, st_new_ptr);
  st_new_ptr->sigl += adj;  /* For all our fldxxx constants, we don't need to
			       borrow or carry. */
  FPU_settag0(current_i387_yuan_   tag);
  clear_C1();
}

/* A fast way to find out whether x is one of RC_DOWN or RC_CHOP
   (and not one of RC_RND or RC_UP).
   */
#define DOWN_OR_CHOP(x)  (x & RC_DOWN)

static void fld1(current_i387_definefunyuan_   int rc)
{
  fld_const(current_i387_yuan_     &CONST_1, 0, TAG_Valid);
}

static void fldl2t(current_i387_definefunyuan_   int rc)
{
  fld_const(current_i387_yuan_     &CONST_L2T, (rc == RC_UP) ? 1 : 0, TAG_Valid);
}

static void fldl2e(current_i387_definefunyuan_   int rc)
{
  fld_const(current_i387_yuan_     &CONST_L2E, DOWN_OR_CHOP(rc) ? -1 : 0, TAG_Valid);
}

static void fldpi(current_i387_definefunyuan_   int rc)
{
  fld_const(current_i387_yuan_     &CONST_PI, DOWN_OR_CHOP(rc) ? -1 : 0, TAG_Valid);
}

static void fldlg2(current_i387_definefunyuan_   int rc)
{
  fld_const(current_i387_yuan_     &CONST_LG2, DOWN_OR_CHOP(rc) ? -1 : 0, TAG_Valid);
}

static void fldln2(current_i387_definefunyuan_   int rc)
{
  fld_const(current_i387_yuan_     &CONST_LN2, DOWN_OR_CHOP(rc) ? -1 : 0, TAG_Valid);
}

static void fldz(current_i387_definefunyuan_   int rc)
{
  fld_const(current_i387_yuan_     &CONST_Z, 0, TAG_Zero);
}

typedef void (*FUNC_RC)(current_i387_definefunyuan_ int);

static FUNC_RC constants_table[] = {
  fld1, fldl2t, fldl2e, fldpi, fldlg2, fldln2, fldz, (FUNC_RC)FPU_illegal
};

void fconst(current_i387_definefunyuan_void)
{
  (constants_table[FPU_rm])(current_i387_yuan_ control_word & CW_RC);
}
