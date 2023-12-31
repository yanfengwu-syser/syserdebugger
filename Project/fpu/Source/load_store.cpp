/*---------------------------------------------------------------------------+
 |  load_store.c                                                             |
 |  $Id: load_store.c,v 1.4 2002/12/12 15:28:43 cbothamy Exp $
 |                                                                           |
 | This file contains most of the code to interpret the FPU instructions     |
 | which load and store from user memory.                                    |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997                                         |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@suburbia.net             |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | Note:                                                                     |
 |    The file contains code which accesses user memory.                     |
 |    Emulator static data may change when user memory is accessed, due to   |
 |    other processes using the emulator while swapping is in progress.      |
 +---------------------------------------------------------------------------*/
#include "fpu_i387.h"
#include <asm/uaccess.h>

#include "fpu_system.h"
#include "exception.h"
#include "fpu_emu.h"
#include "status_w.h"
#include "control_w.h"


#define _NONE_ 0   /* st0_ptr etc not needed */
#define _REG0_ 1   /* Will be storing st(0) */
#define _PUSH_ 3   /* Need to check for space to push onto stack */
#define _null_ 4   /* Function illegal or not implemented */

#define pop_0()	{ FPU_settag0(current_i387_yuan_   TAG_Empty); top++; }


static u_char const type_table[32] = {
  _PUSH_, _PUSH_, _PUSH_, _PUSH_,
  _null_, _null_, _null_, _null_,
  _REG0_, _REG0_, _REG0_, _REG0_,
  _REG0_, _REG0_, _REG0_, _REG0_,
  _NONE_, _null_, _NONE_, _PUSH_,
  _NONE_, _PUSH_, _null_, _PUSH_,
  _NONE_, _null_, _NONE_, _REG0_,
  _NONE_, _REG0_, _NONE_, _REG0_
  };

u_char const data_sizes_16[32] = {
  4,  4,  8,  2,  0,  0,  0,  0,
  4,  4,  8,  2,  4,  4,  8,  2,
  14, 0, 94, 10,  2, 10,  0,  8,  
  14, 0, 94, 10,  2, 10,  2,  8
};

u_char const data_sizes_32[32] = {
  4,  4,  8,  2,  0,  0,  0,  0,
  4,  4,  8,  2,  4,  4,  8,  2,
  28, 0,108, 10,  2, 10,  0,  8,  
  28, 0,108, 10,  2, 10,  2,  8
};

int FPU_load_store(current_i387_definefunyuan_   u_char type, fpu_addr_modes addr_modes,
		     void *data_address)
{
  FPU_REG loaded_data;
  FPU_REG *st0_ptr;
  u_char st0_tag = TAG_Empty;  /* This is just to stop a gcc warning. */
  u_char loaded_tag;

  st0_ptr = (FPU_REG*) NULL;    /* Initialized just to stop compiler warnings. */

  if ( addr_modes.default_mode & PROTECTED )
    {
      if ( addr_modes.default_mode == SEG32 )
	{
	  if ( access_limit < data_sizes_32[type] )
	    math_abort(current_i387_yuan_   FPU_info,SIGSEGV);
	}
      else if ( addr_modes.default_mode == PM16 )
	{
	  if ( access_limit < data_sizes_16[type] )
	    math_abort(current_i387_yuan_   FPU_info,SIGSEGV);
	}
#ifdef PARANOID
      else
	EXCEPTION(EX_INTERNAL|0x140);
#endif /* PARANOID */
    }

  switch ( type_table[type] )
    {
    case _NONE_:
      break;
    case _REG0_:
      st0_ptr = &st(0);       /* Some of these instructions pop after
				 storing */
      st0_tag = FPU_gettag0(current_i387_yuan_clono  );
      break;
    case _PUSH_:
      {
	if ( FPU_gettagi(current_i387_yuan_   -1) != TAG_Empty )
	  { FPU_stack_overflow(current_i387_yuan_clono  ); return 0; }
	top--;
	st0_ptr = &st(0);
      }
      break;
    case _null_:
      FPU_illegal(current_i387_yuan_clono  );
      return 0;
#ifdef PARANOID
    default:
      EXCEPTION(EX_INTERNAL|0x141);
      return 0;
#endif /* PARANOID */
    }

  switch ( type )
    {
    case 000:       /* fld m32real */
      clear_C1();
      loaded_tag = FPU_load_single(current_i387_yuan_   (float *)data_address, &loaded_data);
      if ( (loaded_tag == TAG_Special)
	   && isNaN(current_i387_yuan_   &loaded_data)
	   && (real_1op_NaN(current_i387_yuan_   &loaded_data) < 0) )
	{
	  top++;
	  break;
	}
      FPU_copy_to_reg0(current_i387_yuan_   &loaded_data, loaded_tag);
      break;
    case 001:      /* fild m32int */
      clear_C1();
      loaded_tag = FPU_load_int32(current_i387_yuan_   (s32 *)data_address, &loaded_data);
      FPU_copy_to_reg0(current_i387_yuan_   &loaded_data, loaded_tag);
      break;
    case 002:      /* fld m64real */
      clear_C1();
      loaded_tag = FPU_load_double(current_i387_yuan_   (double *)data_address, &loaded_data);
      if ( (loaded_tag == TAG_Special)
	   && isNaN(current_i387_yuan_   &loaded_data)
	   && (real_1op_NaN(current_i387_yuan_   &loaded_data) < 0) )
	{
	  top++;
	  break;
	}
      FPU_copy_to_reg0(current_i387_yuan_   &loaded_data, loaded_tag);
      break;
    case 003:      /* fild m16int */
      clear_C1();
      loaded_tag = FPU_load_int16(current_i387_yuan_   (s16 *)data_address, &loaded_data);
      FPU_copy_to_reg0(current_i387_yuan_   &loaded_data, loaded_tag);
      break;
    case 010:      /* fst m32real */
      clear_C1();
      FPU_store_single(current_i387_yuan_   st0_ptr, st0_tag, (float *)data_address);
      break;
    case 011:      /* fist m32int */
      clear_C1();
      FPU_store_int32(current_i387_yuan_   st0_ptr, st0_tag, (s32 *)data_address);
      break;
    case 012:     /* fst m64real */
      clear_C1();
      FPU_store_double(current_i387_yuan_   st0_ptr, st0_tag, (double *)data_address);
      break;
    case 013:     /* fist m16int */
      clear_C1();
      FPU_store_int16(current_i387_yuan_   st0_ptr, st0_tag, (s16 *)data_address);
      break;
    case 014:     /* fstp m32real */
      clear_C1();
      if ( FPU_store_single(current_i387_yuan_   st0_ptr, st0_tag, (float *)data_address) )
	pop_0();  /* pop only if the number was actually stored
		     (see the 80486 manual p16-28) */
      break;
    case 015:     /* fistp m32int */
      clear_C1();
      if ( FPU_store_int32(current_i387_yuan_   st0_ptr, st0_tag, (s32 *)data_address) )
	pop_0();  /* pop only if the number was actually stored
		     (see the 80486 manual p16-28) */
      break;
    case 016:     /* fstp m64real */
      clear_C1();
      if ( FPU_store_double(current_i387_yuan_   st0_ptr, st0_tag, (double *)data_address) )
	pop_0();  /* pop only if the number was actually stored
		     (see the 80486 manual p16-28) */
      break;
    case 017:     /* fistp m16int */
      clear_C1();
      if ( FPU_store_int16(current_i387_yuan_   st0_ptr, st0_tag, (s16 *)data_address) )
	pop_0();  /* pop only if the number was actually stored
		     (see the 80486 manual p16-28) */
      break;
    case 020:     /* fldenv  m14/28byte */
      fldenv(current_i387_yuan_   addr_modes, (u_char *)data_address);
      /* Ensure that the values just loaded are not changed by
	 fix-up operations. */
      return 1;
    case 022:     /* frstor m94/108byte */
      frstor(current_i387_yuan_   addr_modes, (u_char *)data_address);
      /* Ensure that the values just loaded are not changed by
	 fix-up operations. */
      return 1;
    case 023:     /* fbld m80dec */
      clear_C1();
      loaded_tag = FPU_load_bcd(current_i387_yuan_   (u_char *)data_address);
      FPU_settag0(current_i387_yuan_   loaded_tag);
      break;
    case 024:     /* fldcw */
      RE_ENTRANT_CHECK_OFF;
      FPU_verify_area(VERIFY_READ, data_address, 2);
      FPU_get_user(control_word, (u16 *) data_address);
      RE_ENTRANT_CHECK_ON;
      if ( partial_status & ~control_word & CW_Exceptions )
	partial_status |= (SW_Summary | SW_Backward);
      else
	partial_status &= ~(SW_Summary | SW_Backward);
#ifdef PECULIAR_486
      control_word |= 0x40;  /* An 80486 appears to always set this bit */
#endif /* PECULIAR_486 */
      return 1;
    case 025:      /* fld m80real */
      clear_C1();
      loaded_tag = FPU_load_extended(current_i387_yuan_   (long double *)data_address, 0);
      FPU_settag0(current_i387_yuan_   loaded_tag);
      break;
    case 027:      /* fild m64int */
      clear_C1();
      loaded_tag = FPU_load_int64(current_i387_yuan_   (s64 *)data_address);
      FPU_settag0(current_i387_yuan_   loaded_tag);
      break;
    case 030:     /* fstenv  m14/28byte */
      fstenv(current_i387_yuan_   addr_modes, (u_char *)data_address);
      return 1;
    case 032:      /* fsave */
      fsave(current_i387_yuan_   addr_modes, (u_char *)data_address);
      return 1;
    case 033:      /* fbstp m80dec */
      clear_C1();
      if ( FPU_store_bcd(current_i387_yuan_   st0_ptr, st0_tag, (u_char *)data_address) )
	pop_0();  /* pop only if the number was actually stored
		     (see the 80486 manual p16-28) */
      break;
    case 034:      /* fstcw m16int */
      RE_ENTRANT_CHECK_OFF;
      FPU_verify_area(VERIFY_WRITE,data_address,2);
      FPU_put_user(control_word, (u16 *) data_address);
      RE_ENTRANT_CHECK_ON;
      return 1;
    case 035:      /* fstp m80real */
      clear_C1();
      if ( FPU_store_extended(current_i387_yuan_   st0_ptr, st0_tag, (long double *)data_address) )
	pop_0();  /* pop only if the number was actually stored
		     (see the 80486 manual p16-28) */
      break;
    case 036:      /* fstsw m2byte */
      RE_ENTRANT_CHECK_OFF;
      FPU_verify_area(VERIFY_WRITE,data_address,2);
      FPU_put_user(status_word(),(u16 *) data_address);
      RE_ENTRANT_CHECK_ON;
      return 1;
    case 037:      /* fistp m64int */
      clear_C1();
      if ( FPU_store_int64(current_i387_yuan_   st0_ptr, st0_tag, (s64 *)data_address) )
	pop_0();  /* pop only if the number was actually stored
		     (see the 80486 manual p16-28) */
      break;
    }
  return 0;
}
