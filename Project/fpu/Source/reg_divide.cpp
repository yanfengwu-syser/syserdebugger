/*---------------------------------------------------------------------------+
 |  reg_divide.c                                                             |
 |  $Id: reg_divide.c,v 1.4 2001/10/06 03:53:46 bdenney Exp $
 |                                                                           |
 | Divide one FPU_REG by another and put the result in a destination FPU_REG.|
 |                                                                           |
 | Copyright (C) 1996                                                        |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@jacobi.maths.monash.edu.au                |
 |                                                                           |
 |    Return value is the tag of the answer, or-ed with FPU_Exception if     |
 |    one was raised, or -1 on internal error.                               |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | The destination may be any FPU_REG, including one of the source FPU_REGs. |
 +---------------------------------------------------------------------------*/
#include "fpu_i387.h"
#include "exception.h"
#include "reg_constant.h"
#include "fpu_emu.h"
#include "fpu_system.h"

/*
  Divide one register by another and put the result into a third register.
bbd: arg2 used to be an int, see comments on FPU_sub.
  */
int FPU_div(current_i387_definefunyuan_   int flags, FPU_REG *rm, int control_w)
{
  FPU_REG x, y;
  FPU_REG const *a, *b, *st0_ptr, *st_ptr;
  FPU_REG *dest;
  u_char taga, tagb, signa, signb, sign, saved_sign;
  int tag, deststnr;
  int rmint = PTR2INT(rm);

  if ( flags & DEST_RM )
    deststnr = rmint;
  else
    deststnr = 0;

  if ( flags & REV )
    {
      b = &st(0);
      st0_ptr = b;
      tagb = FPU_gettag0(current_i387_yuan_clono  );
      if ( flags & LOADED )
	{
	  a = rm;
	  taga = flags & 0x0f;
	}
      else
	{
	  a = &st(rmint);
	  st_ptr = a;
	  taga = FPU_gettagi(current_i387_yuan_   rmint);
	}
    }
  else
    {
      a = &st(0);
      st0_ptr = a;
      taga = FPU_gettag0(current_i387_yuan_clono  );
      if ( flags & LOADED )
	{
	  b = rm;
	  tagb = flags & 0x0f;
	}
      else
	{
	  b = &st(rmint);
	  st_ptr = b;
	  tagb = FPU_gettagi(current_i387_yuan_   rmint);
	}
    }

  signa = getsign(a);
  signb = getsign(b);

  sign = signa ^ signb;

  dest = &st(deststnr);
  saved_sign = getsign(dest);

  if ( !(taga | tagb) )
    {
      /* Both regs Valid, this should be the most common case. */
      reg_copy(a, &x);
      reg_copy(b, &y);
      setpositive(&x);
      setpositive(&y);
      tag = FPU_u_div(current_i387_yuan_   &x, &y, dest, control_w, sign);

      if ( tag < 0 )
	return tag;

      FPU_settagi(current_i387_yuan_   deststnr, tag);
      return tag;
    }

  if ( taga == TAG_Special )
    taga = FPU_Special(current_i387_yuan_   a);
  if ( tagb == TAG_Special )
    tagb = FPU_Special(current_i387_yuan_   b);

  if ( ((taga == TAG_Valid) && (tagb == TW_Denormal))
	    || ((taga == TW_Denormal) && (tagb == TAG_Valid))
	    || ((taga == TW_Denormal) && (tagb == TW_Denormal)) )
    {
      if ( denormal_operand(current_i387_yuan_le   ) < 0 )
	return FPU_Exception;

      FPU_to_exp16(current_i387_yuan_   a, &x);
      FPU_to_exp16(current_i387_yuan_   b, &y);
      tag = FPU_u_div(current_i387_yuan_   &x, &y, dest, control_w, sign);
      if ( tag < 0 )
	return tag;

      FPU_settagi(current_i387_yuan_   deststnr, tag);
      return tag;
    }
  else if ( (taga <= TW_Denormal) && (tagb <= TW_Denormal) )
    {
      if ( tagb != TAG_Zero )
	{
	  /* Want to find Zero/Valid */
	  if ( tagb == TW_Denormal )
	    {
	      if ( denormal_operand(current_i387_yuan_le   ) < 0 )
		return FPU_Exception;
	    }

	  /* The result is zero. */
	  FPU_copy_to_regi(current_i387_yuan_   &CONST_Z, TAG_Zero, deststnr);
	  setsign(dest, sign);
	  return TAG_Zero;
	}
      /* We have an exception condition, either 0/0 or Valid/Zero. */
      if ( taga == TAG_Zero )
	{
	  /* 0/0 */
	  return arith_invalid(current_i387_yuan_   deststnr);
	}
      /* Valid/Zero */
      return FPU_divide_by_zero(current_i387_yuan_   deststnr, sign);
    }
  /* Must have infinities, NaNs, etc */
  else if ( (taga == TW_NaN) || (tagb == TW_NaN) )
    {
      if ( flags & LOADED )
	return real_2op_NaN(current_i387_yuan_   (FPU_REG *)rm, flags & 0x0f, 0, st0_ptr);

      if ( flags & DEST_RM )
	{
	  int tag;
	  tag = FPU_gettag0(current_i387_yuan_clono  );
	  if ( tag == TAG_Special )
	    tag = FPU_Special(current_i387_yuan_   st0_ptr);
	  return real_2op_NaN(current_i387_yuan_   st0_ptr, tag, rmint, (flags & REV) ? st0_ptr : &st(rmint));
	}
      else
	{
	  int tag;
	  tag = FPU_gettagi(current_i387_yuan_   rmint);
	  if ( tag == TAG_Special )
	    tag = FPU_Special(current_i387_yuan_   &st(rmint));
	  return real_2op_NaN(current_i387_yuan_   &st(rmint), tag, 0, (flags & REV) ? st0_ptr : &st(rmint));
	}
    }
  else if (taga == TW_Infinity)
    {
      if (tagb == TW_Infinity)
	{
	  /* infinity/infinity */
	  return arith_invalid(current_i387_yuan_   deststnr);
	}
      else
	{
	  /* tagb must be Valid or Zero */
	  if ( (tagb == TW_Denormal) && (denormal_operand(current_i387_yuan_le   ) < 0) )
	    return FPU_Exception;
	  
	  /* Infinity divided by Zero or Valid does
	     not raise and exception, but returns Infinity */
	  FPU_copy_to_regi(current_i387_yuan_   a, TAG_Special, deststnr);
	  setsign(dest, sign);
	  return taga;
	}
    }
  else if (tagb == TW_Infinity)
    {
      if ( (taga == TW_Denormal) && (denormal_operand(current_i387_yuan_le   ) < 0) )
	return FPU_Exception;

      /* The result is zero. */
      FPU_copy_to_regi(current_i387_yuan_   &CONST_Z, TAG_Zero, deststnr);
      setsign(dest, sign);
      return TAG_Zero;
    }
#ifdef PARANOID
  else
    {
      EXCEPTION(EX_INTERNAL|0x102);
      return FPU_Exception;
    }
#endif /* PARANOID */

}
