/////////////////////////////////////////////////////////////////////////
// $Id: fpu_proto.h,v 1.4 2001/10/06 04:35:13 bdenney Exp $
/////////////////////////////////////////////////////////////////////////
//
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
// bochs.h is the master header file for all C++ code.  It includes all 
// the system header files needed by bochs, and also includes all the bochs
// C++ header files.  Because bochs.h and the files that it includes has 
// structure and class definitions, it cannot be called from C code.
// 

#ifndef _FPU_PROTO_H
#define _FPU_PROTO_H

#include "../../IntelCPU/Source/x86cpu.h"
#include "fpu_i387.h"


asmlinkage int FPU_normalize_nuo(current_i387_definefunyuan_   FPU_REG *x, int bias);
asmlinkage int FPU_u_sub(current_i387_definefunyuan_   FPU_REG const *arg1, FPU_REG const *arg2,
			 FPU_REG *answ, u16 control_w, u_char sign,
			 s32 expa, s32 expb);
asmlinkage int FPU_u_mul(current_i387_definefunyuan_   FPU_REG const *arg1, FPU_REG const *arg2,
			 FPU_REG *answ, u16 control_w, u_char sign,
			 s32 expon);
asmlinkage int FPU_u_div(current_i387_definefunyuan_   FPU_REG const *arg1, FPU_REG const *arg2,
			 FPU_REG *answ, u16 control_w, u_char sign);
asmlinkage int FPU_u_add(current_i387_definefunyuan_   FPU_REG const *arg1, FPU_REG const *arg2,
			 FPU_REG *answ, u16 control_w, u_char sign,
			 s32 expa, s32 expb);
asmlinkage int wm_sqrt(current_i387_definefunyuan_   FPU_REG *n, int dummy1, int dummy2,
		       u16 control_w, u_char sign);
asmlinkage u32	FPU_shrx(current_i387_definefunyuan_     void*l, u32 x);
asmlinkage u32	FPU_shrxs(current_i387_definefunyuan_     void*v, u32 x);
asmlinkage u32 FPU_div_small(current_i387_definefunyuan_   u64 *x, u32 y);
asmlinkage int FPU_round(current_i387_definefunyuan_   FPU_REG *arg, u32 extent, int dummy,
			 u16 control_w, u_char sign);


/* errors.c */
extern void Un_impl(current_i387_definefunyuan_void);
extern void FPU_illegal(current_i387_definefunyuan_void);
extern void FPU_printall(current_i387_definefunyuan_void);
asmlinkage void FPU_exception(current_i387_definefunyuan_   int n);
extern int real_1op_NaN(current_i387_definefunyuan_   FPU_REG *a);
extern int real_2op_NaN(current_i387_definefunyuan_   FPU_REG const *b, u_char tagb, int deststnr,
			FPU_REG const *defaultNaN);
extern int arith_invalid(current_i387_definefunyuan_   int deststnr);
extern int FPU_divide_by_zero(current_i387_definefunyuan_   int deststnr, u_char sign);
extern int set_precision_flag(current_i387_definefunyuan_   int flags);
extern void set_precision_flag_up(current_i387_definefunyuan_void);
extern void set_precision_flag_down(current_i387_definefunyuan_void);
extern int denormal_operand(current_i387_definefunyuan_void);
extern int arith_overflow(current_i387_definefunyuan_   FPU_REG *dest);
extern int arith_round_overflow(current_i387_definefunyuan_   FPU_REG *dest, u8 sign);
extern int arith_underflow(current_i387_definefunyuan_   FPU_REG *dest);
extern void FPU_stack_overflow(current_i387_definefunyuan_void);
extern void FPU_stack_underflow(current_i387_definefunyuan_void);
extern void FPU_stack_underflow_i(current_i387_definefunyuan_   int i);
extern void FPU_stack_underflow_pop(current_i387_definefunyuan_   int i);
/* fpu_arith.c */
extern void fadd__(current_i387_definefunyuan_void);
extern void fmul__(current_i387_definefunyuan_void);
extern void fsub__(current_i387_definefunyuan_void);
extern void fsubr_(current_i387_definefunyuan_void);
extern void fdiv__(current_i387_definefunyuan_void);
extern void fdivr_(current_i387_definefunyuan_void);
extern void fadd_i(current_i387_definefunyuan_void);
extern void fmul_i(current_i387_definefunyuan_void);
extern void fsubri(current_i387_definefunyuan_void);
extern void fsub_i(current_i387_definefunyuan_void);
extern void fdivri(current_i387_definefunyuan_void);
extern void fdiv_i(current_i387_definefunyuan_void);
extern void faddp_(current_i387_definefunyuan_void);
extern void fmulp_(current_i387_definefunyuan_void);
extern void fsubrp(current_i387_definefunyuan_void);
extern void fsubp_(current_i387_definefunyuan_void);
extern void fdivrp(current_i387_definefunyuan_void);
extern void fdivp_(current_i387_definefunyuan_void);
/* fpu_aux.c */
extern void fclex(current_i387_definefunyuan_void);
extern void finit(current_i387_definefunyuan_void);
extern void finit_(current_i387_definefunyuan_void);
extern void fstsw_(current_i387_definefunyuan_void);
extern void fp_nop(current_i387_definefunyuan_void);
extern void fld_i_(current_i387_definefunyuan_void);
extern void fxch_i(current_i387_definefunyuan_void);
extern void ffree_(current_i387_definefunyuan_void);
extern void ffreep(current_i387_definefunyuan_void);
extern void fst_i_(current_i387_definefunyuan_void);
extern void fstp_i(current_i387_definefunyuan_void);
/* fpu_entry.c */
extern void math_emulate(current_i387_definefunyuan_   long arg);
extern void math_abort(current_i387_definefunyuan_   struct info *info, unsigned int signal);
/* fpu_etc.c */
extern void FPU_etc(current_i387_definefunyuan_void);
/* fpu_tags.c */
extern int FPU_gettag0(current_i387_definefunyuan_void);
extern int FPU_gettagi(current_i387_definefunyuan_   int stnr);
extern int FPU_gettag(current_i387_definefunyuan_   int regnr);
extern void FPU_settag0(current_i387_definefunyuan_   int tag);
extern void FPU_settagi(current_i387_definefunyuan_   int stnr, int tag);
extern void FPU_settag(current_i387_definefunyuan_   int regnr, int tag);
extern int FPU_Special(current_i387_definefunyuan_   FPU_REG const *ptr);
extern int isNaN(current_i387_definefunyuan_   FPU_REG const *ptr);
extern void FPU_pop(current_i387_definefunyuan_void);
extern int FPU_empty_i(current_i387_definefunyuan_   int stnr);
extern int FPU_stackoverflow(current_i387_definefunyuan_   FPU_REG **st_new_ptr);
extern void FPU_sync_tags(current_i387_definefunyuan_void);
extern void FPU_copy_to_regi(current_i387_definefunyuan_   FPU_REG const *r, u_char tag, int stnr);
extern void FPU_copy_to_reg1(current_i387_definefunyuan_   FPU_REG const *r, u_char tag);
extern void FPU_copy_to_reg0(current_i387_definefunyuan_   FPU_REG const *r, u_char tag);
/* fpu_trig.c */
extern void FPU_triga(current_i387_definefunyuan_void);
extern void FPU_trigb(current_i387_definefunyuan_void);
/* get_address.c */
extern void *FPU_get_address(current_i387_definefunyuan_   u_char FPU_modrm, u32 *fpu_eip,
			 struct address *addr, fpu_addr_modes addr_modes);
extern void *FPU_get_address_16(current_i387_definefunyuan_   u_char FPU_modrm, u32 *fpu_eip,
			    struct address *addr, fpu_addr_modes addr_modes);
/* load_store.c */
extern int FPU_load_store(current_i387_definefunyuan_   u_char type, fpu_addr_modes addr_modes,
			    void *data_address);
/* poly_2xm1.c */
extern int poly_2xm1(current_i387_definefunyuan_   u_char sign, FPU_REG *arg, FPU_REG *result);
/* poly_atan.c */
extern void poly_atan(current_i387_definefunyuan_   FPU_REG *st0_ptr, u_char st0_tag, FPU_REG *st1_ptr,
		      u_char st1_tag);
/* poly_l2.c */
extern void poly_l2(current_i387_definefunyuan_   FPU_REG *st0_ptr, FPU_REG *st1_ptr, u_char st1_sign);
extern int poly_l2p1(current_i387_definefunyuan_   u_char s0, u_char s1, FPU_REG *r0, FPU_REG *r1,
		     FPU_REG *d);
/* poly_sin.c */
extern void poly_sine(current_i387_definefunyuan_   FPU_REG *st0_ptr);
extern void poly_cos(current_i387_definefunyuan_   FPU_REG *st0_ptr);
/* poly_tan.c */
extern void poly_tan(current_i387_definefunyuan_   FPU_REG *st0_ptr, int flag);
/* reg_add_sub.c */
extern int FPU_add(current_i387_definefunyuan_   FPU_REG const *b, u_char tagb, int destrnr, u16 control_w);
extern int FPU_sub(current_i387_definefunyuan_   int flags, FPU_REG *rm, u16 control_w);   // bbd: changed arg2 from int to FPU_REG*
/* reg_compare.c */
extern int FPU_compare_st_data(current_i387_definefunyuan_   FPU_REG const *loaded_data, u_char loaded_tag);
extern void fcom_st(current_i387_definefunyuan_void);
extern void fcompst(current_i387_definefunyuan_void);
extern void fcompp(current_i387_definefunyuan_void);
extern void fucom_(current_i387_definefunyuan_void);
extern void fucomp(current_i387_definefunyuan_void);
extern void fucompp(current_i387_definefunyuan_void);
/* reg_constant.c */
extern void fconst(current_i387_definefunyuan_void);
/* reg_ld_str.c */
extern int FPU_load_extended(current_i387_definefunyuan_   long double *s, int stnr);
extern int FPU_load_double(current_i387_definefunyuan_   double *dfloat, FPU_REG *loaded_data);
extern int FPU_load_single(current_i387_definefunyuan_   float *single, FPU_REG *loaded_data);
extern int FPU_load_int64(current_i387_definefunyuan_   s64 *_s);
extern int FPU_load_int32(current_i387_definefunyuan_   s32 *_s, FPU_REG *loaded_data);
extern int FPU_load_int16(current_i387_definefunyuan_   s16 *_s, FPU_REG *loaded_data);
extern int FPU_load_bcd(current_i387_definefunyuan_   u_char *s);
extern int FPU_store_extended(current_i387_definefunyuan_   FPU_REG *st0_ptr, u_char st0_tag,
			      long double *d);
extern int FPU_store_double(current_i387_definefunyuan_   FPU_REG *st0_ptr, u_char st0_tag, double *dfloat);
extern int FPU_store_single(current_i387_definefunyuan_   FPU_REG *st0_ptr, u_char st0_tag, float *single);
extern int FPU_store_int64(current_i387_definefunyuan_   FPU_REG *st0_ptr, u_char st0_tag, s64 *d);
extern int FPU_store_int32(current_i387_definefunyuan_   FPU_REG *st0_ptr, u_char st0_tag, s32 *d);
extern int FPU_store_int16(current_i387_definefunyuan_   FPU_REG *st0_ptr, u_char st0_tag, s16 *d);
extern int FPU_store_bcd(current_i387_definefunyuan_   FPU_REG *st0_ptr, u_char st0_tag, u_char *d);
extern int FPU_round_to_int(current_i387_definefunyuan_   FPU_REG *r, u_char tag);
extern u_char *fldenv(current_i387_definefunyuan_   fpu_addr_modes addr_modes, u_char *s);
extern void frstor(current_i387_definefunyuan_   fpu_addr_modes addr_modes, u_char *data_address);
extern u_char *fstenv(current_i387_definefunyuan_   fpu_addr_modes addr_modes, u_char *d);
extern void fsave(current_i387_definefunyuan_   fpu_addr_modes addr_modes, u_char *data_address);
extern int FPU_tagof(current_i387_definefunyuan_   FPU_REG *ptr);
/* reg_mul.c */
extern int FPU_mul(current_i387_definefunyuan_   FPU_REG const *b, u_char tagb, int deststnr, int control_w);

extern int FPU_div(current_i387_definefunyuan_   int flags, FPU_REG *regrm, int control_w); // bbd: changed arg2 from int to FPU_REG*
/* reg_convert.c */
extern int FPU_to_exp16(current_i387_definefunyuan_   FPU_REG const *a, FPU_REG *x);


/*
vex86 error LNK2019: unresolved external symbol "void __cdecl fpu_set_ax(struct BX_FCPU_I387 *,unsigned short)" (?fpu_set_ax@@YAXPAUBX_FCPU_I387@@G@Z)
referenced in function "void __cdecl fstsw_ax(struct BX_FCPU_I387 *)" (?fstsw_ax@@YAXPAUBX_FCPU_I387@@@Z)
vex86 error LNK2019: unresolved external symbol "void __cdecl div_Xsig(struct Xsig const *,struct Xsig const *,struct Xsig *)" (?div_Xsig@@YAXPBUXsig@@0PAU1@@Z)
referenced in function "int __cdecl poly_2xm1(struct BX_FCPU_I387 *,unsigned char,struct fpu__reg *,struct fpu__reg *)" (?poly_2xm1@@YAHPAUBX_FCPU_I387@@EPAUfpu__reg@@1@Z)
vex86 error LNK2019: unresolved external symbol "void __cdecl div_Xsig(struct Xsig const *,struct Xsig const *,struct Xsig *)" (?div_Xsig@@YAXPBUXsig@@0PAU1@@Z)
referenced in function "void __cdecl poly_tan(struct BX_FCPU_I387 *,struct fpu__reg *,int)" (?poly_tan@@YAXPAUBX_FCPU_I387@@PAUfpu__reg@@H@Z)
vex86 error LNK2001: unresolved external symbol "void __cdecl div_Xsig(struct Xsig const *,struct Xsig const *,struct Xsig *)" (?div_Xsig@@YAXPBUXsig@@0PAU1@@Z)
vex86 error LNK2019: unresolved external symbol "void __cdecl div_Xsig(struct Xsig const *,struct Xsig const *,struct Xsig *)" (?div_Xsig@@YAXPBUXsig@@0PAU1@@Z) 
referenced in function "void __cdecl poly_atan(struct BX_FCPU_I387 *,struct fpu__reg *,unsigned char,struct fpu__reg *,unsigned char)" (?poly_atan@@YAXPAUBX_FCPU_I387@@PAUfpu__reg@@E1E@Z)
*/



#endif /* _FPU_PROTO_H */

